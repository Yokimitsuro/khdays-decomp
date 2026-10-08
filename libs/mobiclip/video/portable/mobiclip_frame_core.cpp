/* MobiClip frame decoder entry: the payload's MobiClip_DecodeFrameCore (0x0208dfb4) in portable
 * C++. See mobiclip_frame_core.h for the state it works on.
 *
 * The payload keeps no state between frames beyond what this writes back: the planes, the
 * quantizer, the format bit, the coefficient table, the quant/scan tables built from the
 * quantizer, and the borders of the prediction-mode cache. Everything else it touches in the
 * state is scratch for the frame being decoded.
 *
 * The cache's borders are the one place the payload reads what an earlier frame left: its
 * quant-table setup (MobiClip_SetupQuantTables, 0x02091218) also marks the top row (+1..+4) and
 * the left column (+8, +16, +24, +32) of the cache "unavailable" (9), its frame decoder runs that
 * setup only when the quantizer changes (`cmp r5,r4; blne` at 0x0208e11c, `blne` at 0x0208dfe8),
 * and nothing else writes those bytes: each block reads its neighbours at -1 and -8 and writes
 * only the interior. A frame decoded with the quantizer of the one before reads the borders as
 * they were left.
 */
#include "mobiclip_frame_core.h"
#include "mobiclip_reference.hpp"

namespace {

/* The payload reads the bitstream as it goes and has no length for it. The semantic reader wants
 * one; this only has to cover the largest packet (the packed size field is 18 bits), since the
 * reader never looks further ahead than the decode consumes. */
const unsigned int kBitstreamBound = 1u << 18;

/* One motion vector per 16-pixel macroblock column, plus the left/upper neighbours. */
const unsigned int kMotionScratch = MOBICLIP_PLANE_STRIDE / 16 + 3;

/* The prediction-mode cache's border entries and the value that marks them unavailable. */
const unsigned char kPredictionBorder[] = {1, 2, 3, 4, 8, 16, 24, 32};
const unsigned char kPredictionUnavailable = 9;

khdays::mobiclip::CoefficientTable coefficientTable(const unsigned char *table)
{
    khdays::mobiclip::CoefficientTable out;
    out.lookup = reinterpret_cast<const unsigned short *>(table);
    out.residue = table + 4096 * 2;
    return out;
}

} // namespace

extern "C" int MobiClip_DecodeFrameCore(MobiClipDecoderState *pState)
{
    using namespace khdays::mobiclip;

    const unsigned int stride = MOBICLIP_PLANE_STRIDE;
    const unsigned int half = MOBICLIP_PLANE_STRIDE / 2;
    CoefficientTable tables[2];
    DecoderReferenceFrame histories[5];
    DecoderFrameBuffer output;
    MotionVector motion[kMotionScratch];
    DecoderFrameResult result;
    unsigned int i;

    if (pState == 0 || pState->nWidth > stride)
        return 0;

    tables[0] = coefficientTable(pState->apCoefficientTables[0]);
    tables[1] = coefficientTable(pState->apCoefficientTables[1]);

    for (i = 0; i < 5; ++i) {
        histories[i].luma = pState->apLuma[i + 1];
        histories[i].chromaFirst = pState->apChroma[i + 1];
        histories[i].chromaSecond = pState->apChroma[i + 1] + half;
        histories[i].lumaStride = stride;
        histories[i].chromaStride = stride;
    }
    output.luma = pState->apLuma[0];
    output.chromaFirst = pState->apChroma[0];
    output.chromaSecond = pState->apChroma[0] + half;
    output.lumaStride = stride;
    output.chromaStride = stride;

    if (!decodeFrame(pState->pBitstream, kBitstreamBound, pState->nWidth, pState->nHeight, tables,
                     histories, 5, pState->nQuantizer, pState->bFormatVariant != 0, output,
                     motion, kMotionScratch, result))
        return 0;

    pState->nQuantizer = result.header.quantizer;
    pState->bFormatVariant = result.header.formatVariant ? 1 : 0;
    pState->pCoefficientTable = pState->apCoefficientTables[result.header.coefficientTableVariant];
    buildQuantScanTables(result.header.quantizer, pState->aQuantScan8x8, pState->aQuantScan4x4);
    for (i = 0; i < sizeof kPredictionBorder; ++i)
        pState->aPredictionModes[kPredictionBorder[i]] = kPredictionUnavailable;

    /* The bitstream is consumed in 16-bit words. */
    return (int)((result.bitsConsumed + 15) / 16 * 2);
}
