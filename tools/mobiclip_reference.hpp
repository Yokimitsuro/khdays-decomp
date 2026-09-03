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

// MobiClip refills its MSB-first reservoir with little-endian uint16 words.
// This bounded semantic reader exposes the same bit order without relying on
// the payload's private r1/r2/r3 register convention.
class WordBitReader {
public:
    WordBitReader(const unsigned char *data, unsigned int sizeBytes);

    unsigned int bitPosition() const;
    bool readBit(unsigned int &value);
    bool readBits(unsigned int count, unsigned int &value);
    bool readUnsignedExpGolomb(unsigned int &value);
    bool readSignedExpGolomb(int &value);

private:
    const unsigned char *data_;
    unsigned int sizeBytes_;
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

// Restores the border sentinels written by MobiClip_SetupQuantTables. Other
// prediction-cache entries are preserved.
void resetPredictionBorders(unsigned char predictionModes[40]);

// Applies already-decoded VLC symbols exactly as the tail of
// MobiClip_DecodeRunLevelCoefficients does. Returns false for an unterminated
// sequence or a run outside the selected 4x4/8x8 table.
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

} // namespace mobiclip
} // namespace khdays

#endif
