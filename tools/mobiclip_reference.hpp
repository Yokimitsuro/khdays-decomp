#ifndef KHDAYS_TOOLS_MOBICLIP_REFERENCE_HPP
#define KHDAYS_TOOLS_MOBICLIP_REFERENCE_HPP

namespace khdays {
namespace mobiclip {

struct QuantizedCoefficient {
    unsigned int index;
    int value;
};

struct RunLevelSymbol {
    unsigned int run;
    int level;
    bool last;
};

struct FrameHeader {
    bool intra;
    bool formatVariant;
    unsigned int coefficientTableVariant;
    unsigned int quantizer;
};

struct MotionVector {
    int x;
    int y;
};

enum InlineModeCodebook {
    ModePFrameMacroblock = 0,
    ModeMotion16,
    ModeMotion8x16,
    ModeIntra16,
    ModeMotion8x8,
    ModeMotion16x4,
    ModeMotion16x2,
    ModeMotion8x8Alt,
    ModePredictedA,
    ModePredictedB,
    ModePredictedC,
    ModePredictedD,
    ModePredictedE,
    ModePredictedF,
    ModePredictedG,
    ModePredictedH,
    ModeCodebookCount
};

struct YCoCgFrame {
    const unsigned char *luma;
    const unsigned char *chroma;
    unsigned int width;
    unsigned int height;
    unsigned int lumaStride;
    unsigned int chromaStride;
};

struct CoefficientTable {
    const unsigned short *lookup;
    const unsigned char *residue;
};

// Caller-owned planar output. chromaFirst/chromaSecond retain bitstream order
// (Cg then Co for the YCoCg MODS variant), matching the Python oracle.
struct DecoderFrameBuffer {
    unsigned char *luma;
    unsigned char *chromaFirst;
    unsigned char *chromaSecond;
    unsigned int lumaStride;
    unsigned int chromaStride;
};

struct DecoderReferenceFrame {
    const unsigned char *luma;
    const unsigned char *chromaFirst;
    const unsigned char *chromaSecond;
    unsigned int lumaStride;
    unsigned int chromaStride;
};

struct DecoderFrameResult {
    FrameHeader header;
    unsigned int bitsConsumed;
};

// MobiClip refills its MSB-first reservoir with little-endian uint16 words.
// This bounded semantic reader exposes the same bit order without relying on
// the payload's private r1/r2/r3 register convention.
class WordBitReader {
public:
    WordBitReader(const unsigned char *data, unsigned int sizeBytes,
                  unsigned int zeroPaddingBytes = 0);

    unsigned int bitPosition() const;
    bool readBit(unsigned int &value);
    bool readBits(unsigned int count, unsigned int &value);
    bool peekBits(unsigned int count, unsigned int &value);
    bool readUnsignedExpGolomb(unsigned int &value);
    bool readSignedExpGolomb(int &value);

private:
    const unsigned char *data_;
    unsigned int sizeBytes_;
    unsigned int zeroPaddingBytes_;
    unsigned int bitPosition_;
};

// Packed table entries use the low byte as the destination scan index and the
// following signed 16 bits as the inverse-quantization multiplier.
QuantizedCoefficient unpackQuantScan(unsigned int entry, int level);

// Builds the exact packed tables stored at decoder-state offsets +0x74 and
// +0x174. Valid Nintendo DS stream quantizers are 12..53.
bool buildQuantScanTables(unsigned int quantizer,
                          unsigned int quantScan8x8[64],
                          unsigned int quantScan4x4[16]);

// Parses the frame prefix consumed by MobiClip_DecodeFrameCore. P-frames keep
// the preceding format bit, force coefficient table 0, and code QP as a
// signed Exp-Golomb delta. I-frames carry format, table variant and absolute
// six-bit QP directly.
bool decodeFrameHeader(WordBitReader &reader,
                       unsigned int previousQuantizer,
                       bool previousFormatVariant,
                       FrameHeader &header);

// P-frame macroblocks predict each component as the median of the left,
// upper-left and upper neighbours, then add two signed Exp-Golomb deltas.
MotionVector medianMotionVector(const MotionVector &left,
                                const MotionVector &upperLeft,
                                const MotionVector &upper);
bool decodePredictedMotion(WordBitReader &reader,
                           const MotionVector &prediction,
                           MotionVector &motion);

// Restores the border sentinels written by MobiClip_SetupQuantTables. Other
// prediction-cache entries are preserved.
void resetPredictionBorders(unsigned char predictionModes[40]);

// Decodes the predicted intra mode and updates the cache at state +0x4c.
// A one bit reuses the neighbour prediction; a zero bit carries a three-bit
// alternative with the predicted value omitted from the alphabet.
bool decodePredictedIntraMode(WordBitReader &reader,
                              unsigned char predictionModes[40],
                              unsigned int blockX,
                              unsigned int blockY,
                              unsigned int size,
                              unsigned int &mode);

// Decode the four compact mode alphabets embedded beside their relative
// dispatch tables. The prefix tables are replicated to permit a single
// 4- or 5-bit lookup; the selected length is then consumed from the stream.
bool decodePFrameMacroblockMode(WordBitReader &reader, unsigned int &mode);
bool decodeMotion16Mode(WordBitReader &reader, unsigned int &mode);
bool decodeMotion8x16Mode(WordBitReader &reader, unsigned int &mode);
bool decodeIntra16Mode(WordBitReader &reader, unsigned int &mode);

// Generic access to all sixteen compact mode contexts embedded in the ARM
// payload.  The dedicated helpers above remain as readable aliases for the
// four top-level contexts recovered first.
bool decodeInlineMode(WordBitReader &reader,
                      InlineModeCodebook codebook,
                      unsigned int &mode);

// Reconstructs one native intra-prediction block in place. Modes 0..8 are
// above, left, delta-plane, DC and the five directional predictors. The
// planeDelta argument is consumed only by mode 2 and is the signed Golomb
// value from the bitstream. Valid block sizes are 4, 8 and 16.
bool predictIntraBlock(unsigned char *frame,
                       unsigned int width,
                       unsigned int height,
                       unsigned int stride,
                       unsigned int blockX,
                       unsigned int blockY,
                       unsigned int size,
                       unsigned int mode,
                       int planeDelta);

// Copies one motion-predicted byte plane. Motion components are half-sample
// units. Fractional phases deliberately average shifted samples separately,
// matching the ARM packed-byte kernels rather than a rounded (a + b) / 2.
bool compensateMotionBlock(const unsigned char *reference,
                           unsigned char *destination,
                           unsigned int frameWidth,
                           unsigned int frameHeight,
                           unsigned int referenceStride,
                           unsigned int destinationStride,
                           unsigned int blockX,
                           unsigned int blockY,
                           unsigned int blockWidth,
                           unsigned int blockHeight,
                           const MotionVector &motion);

// Decodes one signed run/level symbol from the exact Nintendo DS lookup-table
// layout: 4096 packed uint16 entries followed by 256 residue bytes. The API
// takes the two typed regions separately so original table bytes stay local.
bool decodeRunLevelSymbol(WordBitReader &reader,
                          const unsigned short lookup[4096],
                          const unsigned char residue[256],
                          RunLevelSymbol &symbol);

// Clears and fills one coefficient block from already-decoded VLC symbols,
// matching the caller clear plus the placement tail of
// MobiClip_DecodeRunLevelCoefficients. Returns false for an unterminated
// sequence, an invalid block size or an out-of-range run/scan index.
bool placeRunLevelCoefficients(const RunLevelSymbol *symbols,
                               unsigned int symbolCount,
                               const unsigned int *quantScan,
                               unsigned int coefficientCount,
                               int *coefficients);

// These implement the semantic result of the ARM transform paths. Coefficients
// and residuals are row-major. The input is preserved.
void inverseTransform4x4(const int coefficients[16], int residual[16]);
void inverseTransform8x8(const int coefficients[64], int residual[64]);

// Adds a transformed residual to an existing prediction and clips to 0..255.
void addResidual4x4(unsigned char *destination, unsigned int stride,
                   const int coefficients[16]);
void addResidual8x8(unsigned char *destination, unsigned int stride,
                   const int coefficients[64]);

// Complete allocation-free semantic frame decoders. Output planes and motion
// scratch are supplied by the caller, so this API is suitable for both host
// verification and an eventual Nintendo DS integration. The reader supplies
// sixteen virtual zero bytes after sizeBytes, matching the native caller's
// safe look-ahead without requiring the caller to over-allocate the packet.
bool decodeIFrame(const unsigned char *bitstream,
                  unsigned int sizeBytes,
                  unsigned int width,
                  unsigned int height,
                  const CoefficientTable coefficientTables[2],
                  const DecoderFrameBuffer &output,
                  DecoderFrameResult &result);

bool decodePFrame(const unsigned char *bitstream,
                  unsigned int sizeBytes,
                  unsigned int width,
                  unsigned int height,
                  const CoefficientTable &coefficientTable0,
                  const DecoderReferenceFrame *histories,
                  unsigned int historyCount,
                  unsigned int previousQuantizer,
                  bool previousFormatVariant,
                  const DecoderFrameBuffer &output,
                  MotionVector *motionScratch,
                  unsigned int motionScratchCount,
                  DecoderFrameResult &result);

bool decodeFrame(const unsigned char *bitstream,
                 unsigned int sizeBytes,
                 unsigned int width,
                 unsigned int height,
                 const CoefficientTable coefficientTables[2],
                 const DecoderReferenceFrame *histories,
                 unsigned int historyCount,
                 unsigned int previousQuantizer,
                 bool previousFormatVariant,
                 const DecoderFrameBuffer &output,
                 MotionVector *motionScratch,
                 unsigned int motionScratchCount,
                 DecoderFrameResult &result);

// Converts the decoder's native layout to Nintendo DS RGB555:
//   luma: 256-byte rows;
//   chroma: Co in bytes 0..127 and Cg in bytes 128..255 of each row,
//   with the ARM's -4 luma bias applied in a checkerboard pattern,
//           one sample per 2x2 luma pixels.
// The original ARM converter applies a four-unit checkerboard luma correction
// before reducing each channel to five bits.
bool convertYCoCgToRgb555(const YCoCgFrame &frame,
                          unsigned short *destination,
                          unsigned int destinationStridePixels);

} // namespace mobiclip
} // namespace khdays

#endif
