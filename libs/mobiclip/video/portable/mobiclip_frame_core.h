/* MobiClip frame decoder: the entry the game calls, in portable C++.
 *
 * ov024 copies a position-independent ARM payload (data_ov024_0208c8c4, see
 * docs/MOBICLIP_DECODER.md) to ITCM and calls it once per video frame through the pointer at
 * owner +0x38, passing the decoder state kept at owner +0x34:
 *
 *     **(int **)(owner + 0x34) += decode(*(void **)(owner + 0x34));
 *
 * MobiClip_DecodeFrameCore is that routine written out on top of the semantic decoder in
 * mobiclip_reference.cpp. It reads and writes the same state and the same planes, and returns the
 * same byte count; the original ARM stays in the payload source, which is what the ROM build
 * links.
 *
 * The layout below is the ARM9's: pointers are 32-bit.
 */
#ifndef KHDAYS_MOBICLIP_FRAME_CORE_H
#define KHDAYS_MOBICLIP_FRAME_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Planes are addressed with a fixed row stride of 256 bytes. A chroma row holds one half-width
 * plane in bytes 0..127 and the other in bytes 128..255, one sample per 2x2 luma pixels. */
#define MOBICLIP_PLANE_STRIDE 256

typedef struct MobiClipDecoderState {
    const unsigned char *pBitstream;         /* +0x000: the frame's first byte; the caller advances
                                                it by the return value */
    unsigned int nWidth;                     /* +0x004 */
    unsigned int nHeight;                    /* +0x008 */
    unsigned char *apLuma[6];                /* +0x00c: [0] receives the frame, [1..5] are the
                                                previous frames, newest first */
    unsigned char *apChroma[6];              /* +0x024: in the same order */
    const unsigned char *apCoefficientTables[2]; /* +0x03c: run/level tables, 4096 packed u16
                                                    lookups followed by 256 residue bytes */
    const unsigned char *pClampTable;        /* +0x044: reconstruction clamp lookup */
    unsigned int bFormatVariant;             /* +0x048: format bit of the last I-frame; P-frames
                                                keep it */
    unsigned char aPredictionModes[40];      /* +0x04c: intra prediction-mode cache, 8 per row; its
                                                borders (+1..+4, +8, +16, +24, +32) hold 9,
                                                "unavailable", set with the quant/scan tables and
                                                kept between frames */
    unsigned int aQuantScan8x8[64];          /* +0x074: packed scan index | multiplier << 8 */
    unsigned int aQuantScan4x4[16];          /* +0x174 */
    int aTransformWorkspace[128];            /* +0x1b4: coefficient and inverse-transform
                                                scratch */
    unsigned int nQuantizer;                 /* +0x3b4: the last frame's quantizer */
    const unsigned char *pCoefficientTable;  /* +0x3b8: the table the last frame used */
    int aPredictedMotion[2];                 /* +0x3bc: median-predicted motion vector (x, y) */
    int aMotion[18][2];                      /* +0x3c4: per-column motion history and border
                                                slots */
} MobiClipDecoderState;                      /* 0x454 bytes */

/* Decodes the frame at pBitstream into apLuma[0] / apChroma[0] and records its quantizer,
 * format bit and coefficient table in the state. Returns the bytes the frame used, rounded up to
 * the 16-bit words the bitstream is read in, or 0 when the bitstream does not decode. */
int MobiClip_DecodeFrameCore(MobiClipDecoderState *pState);

#ifdef __cplusplus
}
#endif

#endif
