#include "mobiclip_reference.hpp"

namespace khdays {
namespace mobiclip {
namespace {

static const unsigned char kQuant4x4[6][16] = {
    {10, 13, 13, 10, 16, 10, 13, 13, 13, 13, 16, 10, 16, 13, 13, 16},
    {11, 14, 14, 11, 18, 11, 14, 14, 14, 14, 18, 11, 18, 14, 14, 18},
    {13, 16, 16, 13, 20, 13, 16, 16, 16, 16, 20, 13, 20, 16, 16, 20},
    {14, 18, 18, 14, 23, 14, 18, 18, 18, 18, 23, 14, 23, 18, 18, 23},
    {16, 20, 20, 16, 25, 16, 20, 20, 20, 20, 25, 16, 25, 20, 20, 25},
    {18, 23, 23, 18, 29, 18, 23, 23, 23, 23, 29, 18, 29, 23, 23, 29},
};

static const unsigned char kQuant8x8[6][64] = {
    {
        20, 19, 19, 25, 18, 25, 19, 24, 24, 19, 20, 18, 32, 18, 20, 19,
        19, 24, 24, 19, 19, 25, 18, 25, 18, 25, 18, 25, 19, 24, 24, 19,
        19, 24, 24, 19, 18, 32, 18, 20, 18, 32, 18, 24, 24, 19, 19, 24,
        24, 18, 25, 18, 25, 18, 19, 24, 24, 19, 18, 32, 18, 24, 24, 18,
    },
    {
        22, 21, 21, 28, 19, 28, 21, 26, 26, 21, 22, 19, 35, 19, 22, 21,
        21, 26, 26, 21, 21, 28, 19, 28, 19, 28, 19, 28, 21, 26, 26, 21,
        21, 26, 26, 21, 19, 35, 19, 22, 19, 35, 19, 26, 26, 21, 21, 26,
        26, 19, 28, 19, 28, 19, 21, 26, 26, 21, 19, 35, 19, 26, 26, 19,
    },
    {
        26, 24, 24, 33, 23, 33, 24, 31, 31, 24, 26, 23, 42, 23, 26, 24,
        24, 31, 31, 24, 24, 33, 23, 33, 23, 33, 23, 33, 24, 31, 31, 24,
        24, 31, 31, 24, 23, 42, 23, 26, 23, 42, 23, 31, 31, 24, 24, 31,
        31, 23, 33, 23, 33, 23, 24, 31, 31, 24, 23, 42, 23, 31, 31, 23,
    },
    {
        28, 26, 26, 35, 25, 35, 26, 33, 33, 26, 28, 25, 45, 25, 28, 26,
        26, 33, 33, 26, 26, 35, 25, 35, 25, 35, 25, 35, 26, 33, 33, 26,
        26, 33, 33, 26, 25, 45, 25, 28, 25, 45, 25, 33, 33, 26, 26, 33,
        33, 25, 35, 25, 35, 25, 26, 33, 33, 26, 25, 45, 25, 33, 33, 25,
    },
    {
        32, 30, 30, 40, 28, 40, 30, 38, 38, 30, 32, 28, 51, 28, 32, 30,
        30, 38, 38, 30, 30, 40, 28, 40, 28, 40, 28, 40, 30, 38, 38, 30,
        30, 38, 38, 30, 28, 51, 28, 32, 28, 51, 28, 38, 38, 30, 30, 38,
        38, 28, 40, 28, 40, 28, 30, 38, 38, 30, 28, 51, 28, 38, 38, 28,
    },
    {
        36, 34, 34, 46, 32, 46, 34, 43, 43, 34, 36, 32, 58, 32, 36, 34,
        34, 43, 43, 34, 34, 46, 32, 46, 32, 46, 32, 46, 34, 43, 43, 34,
        34, 43, 43, 34, 32, 58, 32, 36, 32, 58, 32, 43, 43, 34, 34, 43,
        43, 32, 46, 32, 46, 32, 34, 43, 43, 34, 32, 58, 32, 43, 43, 32,
    },
};

static const unsigned char kZigzag4x4[16] = {
    0, 4, 1, 2, 5, 8, 12, 9, 6, 3, 7, 10, 13, 14, 11, 15,
};

static const unsigned char kZigzag8x8[64] = {
    0, 1, 8, 16, 9, 2, 3, 10, 17, 24, 32, 25, 18, 11, 4, 5,
    12, 19, 26, 33, 40, 48, 41, 34, 27, 20, 13, 6, 7, 14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63,
};

static const unsigned char kBlock8x8CoefficientMasks[64] = {
    0, 31, 63, 15, 8, 4, 2, 1, 11, 14, 27, 13, 3, 7, 12, 23,
    29, 10, 30, 5, 16, 47, 55, 59, 19, 61, 62, 9, 28, 6, 21, 26,
    51, 17, 18, 20, 24, 32, 60, 53, 25, 22, 58, 48, 49, 50, 39, 52,
    43, 45, 57, 56, 35, 54, 46, 33, 37, 34, 36, 44, 42, 40, 41, 38,
};

static const unsigned char kPFrameBlock8x8CoefficientMasks[64] = {
    0, 15, 4, 1, 8, 2, 12, 3, 5, 10, 13, 7, 14, 11, 31, 9,
    6, 16, 63, 30, 23, 29, 27, 28, 19, 24, 26, 18, 17, 20, 21, 32,
    47, 22, 25, 55, 61, 62, 59, 60, 51, 53, 33, 36, 34, 40, 35, 44,
    48, 39, 45, 37, 58, 43, 46, 42, 49, 52, 56, 50, 41, 38, 57, 54,
};

static const unsigned char kBlock4x4CoefficientMasks[16] = {
    15, 0, 2, 1, 4, 8, 12, 3, 11, 13, 14, 7, 10, 5, 9, 6,
};

static const unsigned char kPFrameBlock4x4CoefficientMasks[16] = {
    0, 4, 1, 8, 2, 12, 3, 5, 10, 15, 7, 13, 14, 11, 9, 6,
};

static const unsigned int kPackedAverageLaneMask = 0x7f7f7f7f;

static const unsigned char kPFrameModePrefix[32] = {
    1, 1, 1, 1, 1, 1, 1, 1, 8, 8, 8, 8, 9, 9, 9, 9,
    4, 3, 2, 2, 7, 7, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0,
};
static const unsigned char kPFrameModeLengths[10] =
    {2, 2, 4, 5, 5, 5, 5, 4, 3, 3};
static const unsigned char kMotion16ModePrefix[16] =
    {0, 0, 0, 0, 9, 9, 5, 4, 2, 2, 3, 8, 1, 1, 1, 1};
static const unsigned char kMotion16ModeLengths[10] =
    {2, 2, 3, 4, 4, 4, 0, 0, 4, 3};
static const unsigned char kMotion8x16ModePrefix[16] =
    {3, 3, 9, 5, 0, 0, 0, 0, 4, 8, 2, 2, 1, 1, 1, 1};
static const unsigned char kMotion8x16ModeLengths[10] =
    {2, 2, 3, 3, 4, 4, 0, 0, 4, 4};
static const unsigned char kIntra16ModePrefix[32] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    3, 3, 3, 3, 4, 4, 8, 5, 2, 2, 2, 2, 0, 0, 0, 0,
};
static const unsigned char kIntra16ModeLengths[10] =
    {3, 1, 3, 3, 4, 5, 0, 0, 5, 0};

static const unsigned char kMotion8x8Prefix[16] =
    {0, 0, 0, 0, 5, 4, 8, 8, 2, 2, 3, 9, 1, 1, 1, 1};
static const unsigned char kMotion8x8Lengths[10] =
    {2, 2, 3, 4, 4, 4, 0, 0, 3, 4};
static const unsigned char kMotion16x4Prefix[16] =
    {0, 0, 0, 0, 3, 3, 8, 4, 2, 2, 5, 9, 1, 1, 1, 1};
static const unsigned char kMotion16x4Lengths[10] =
    {2, 2, 3, 3, 4, 4, 0, 0, 4, 4};
static const unsigned char kMotion16x2Prefix[16] =
    {1, 1, 1, 1, 1, 1, 1, 1, 9, 4, 2, 2, 0, 0, 5, 3};
static const unsigned char kMotion16x2Lengths[10] =
    {3, 1, 3, 4, 4, 4, 0, 0, 0, 4};
static const unsigned char kMotion8x8AltPrefix[16] =
    {0, 0, 0, 0, 3, 3, 5, 9, 4, 8, 2, 2, 1, 1, 1, 1};
static const unsigned char kMotion8x8AltLengths[10] =
    {2, 2, 3, 3, 4, 4, 0, 0, 4, 4};
static const unsigned char kPredictedAPrefix[16] =
    {2, 2, 2, 2, 8, 9, 3, 3, 5, 4, 0, 0, 1, 1, 1, 1};
static const unsigned char kPredictedALengths[10] =
    {3, 2, 2, 3, 4, 4, 0, 0, 4, 4};
static const unsigned char kPredictedBPrefix[16] =
    {2, 2, 2, 2, 4, 4, 9, 5, 3, 3, 0, 0, 1, 1, 1, 1};
static const unsigned char kPredictedBLengths[10] =
    {3, 2, 2, 3, 3, 4, 0, 0, 0, 4};
static const unsigned char kPredictedCPrefix[16] =
    {0, 0, 0, 0, 3, 3, 9, 5, 8, 4, 2, 2, 1, 1, 1, 1};
static const unsigned char kPredictedCLengths[10] =
    {2, 2, 3, 3, 4, 4, 0, 0, 4, 4};
static const unsigned char kPredictedDPrefix[32] = {
    0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 3, 3, 3, 3,
    8, 9, 5, 5, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1,
};
static const unsigned char kPredictedDLengths[10] =
    {2, 2, 3, 3, 3, 4, 0, 0, 5, 5};
static const unsigned char kPredictedEPrefix[16] =
    {0, 0, 0, 0, 4, 4, 9, 5, 3, 3, 2, 2, 1, 1, 1, 1};
static const unsigned char kPredictedELengths[10] =
    {2, 2, 3, 3, 3, 4, 0, 0, 0, 4};
static const unsigned char kPredictedFPrefix[32] = {
    0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 4, 4, 8, 5, 1, 1, 1, 1, 1, 1, 1, 1,
};
static const unsigned char kPredictedFLengths[10] =
    {2, 2, 2, 3, 4, 5, 0, 0, 5, 0};
static const unsigned char kPredictedGPrefix[16] =
    {0, 0, 0, 0, 4, 4, 8, 5, 3, 3, 2, 2, 1, 1, 1, 1};
static const unsigned char kPredictedGLengths[10] =
    {2, 2, 3, 3, 3, 4, 0, 0, 4, 0};
static const unsigned char kPredictedHPrefix[8] =
    {5, 4, 1, 1, 0, 0, 3, 2};
static const unsigned char kPredictedHLengths[10] =
    {2, 2, 3, 3, 3, 3, 0, 0, 0, 0};

struct ModeCodebookDefinition {
    const unsigned char *prefix;
    unsigned int prefixBits;
    const unsigned char *lengths;
};

static const ModeCodebookDefinition kModeCodebooks[ModeCodebookCount] = {
    {kPFrameModePrefix, 5, kPFrameModeLengths},
    {kMotion16ModePrefix, 4, kMotion16ModeLengths},
    {kMotion8x16ModePrefix, 4, kMotion8x16ModeLengths},
    {kIntra16ModePrefix, 5, kIntra16ModeLengths},
    {kMotion8x8Prefix, 4, kMotion8x8Lengths},
    {kMotion16x4Prefix, 4, kMotion16x4Lengths},
    {kMotion16x2Prefix, 4, kMotion16x2Lengths},
    {kMotion8x8AltPrefix, 4, kMotion8x8AltLengths},
    {kPredictedAPrefix, 4, kPredictedALengths},
    {kPredictedBPrefix, 4, kPredictedBLengths},
    {kPredictedCPrefix, 4, kPredictedCLengths},
    {kPredictedDPrefix, 5, kPredictedDLengths},
    {kPredictedEPrefix, 4, kPredictedELengths},
    {kPredictedFPrefix, 5, kPredictedFLengths},
    {kPredictedGPrefix, 4, kPredictedGLengths},
    {kPredictedHPrefix, 3, kPredictedHLengths},
};

static int arithmeticShiftRight(int value, unsigned int shift)
{
    unsigned int bits = (unsigned int)value;
    if (shift == 0)
        return value;
    if (value >= 0)
        return (int)(bits >> shift);
    return (int)((bits >> shift) | (~0u << (32 - shift)));
}

static void inverse4(int values[4])
{
    unsigned int a = (unsigned int)values[0] + (unsigned int)values[2];
    unsigned int b = (unsigned int)values[0] - (unsigned int)values[2];
    unsigned int c = (unsigned int)values[1] +
                     (unsigned int)arithmeticShiftRight(values[3], 1);
    unsigned int d = (unsigned int)arithmeticShiftRight(values[1], 1) -
                     (unsigned int)values[3];

    values[0] = (int)(a + c);
    values[1] = (int)(b + d);
    values[2] = (int)(b - d);
    values[3] = (int)(a - c);
}

static void inverse8(int values[8])
{
    int even[4];
    unsigned int e;
    unsigned int f;
    unsigned int g;
    unsigned int h;
    unsigned int x0;
    unsigned int x1;
    unsigned int x2;
    unsigned int x3;

    even[0] = values[0];
    even[1] = values[2];
    even[2] = values[4];
    even[3] = values[6];
    inverse4(even);

    e = (unsigned int)values[7] + (unsigned int)values[1] -
        (unsigned int)values[3] -
        (unsigned int)arithmeticShiftRight(values[3], 1);
    f = (unsigned int)values[7] - (unsigned int)values[1] +
        (unsigned int)values[5] +
        (unsigned int)arithmeticShiftRight(values[5], 1);
    g = (unsigned int)values[5] - (unsigned int)values[3] -
        (unsigned int)values[7] -
        (unsigned int)arithmeticShiftRight(values[7], 1);
    h = (unsigned int)values[5] + (unsigned int)values[3] +
        (unsigned int)values[1] +
        (unsigned int)arithmeticShiftRight(values[1], 1);

    x3 = g + (unsigned int)arithmeticShiftRight((int)h, 2);
    x2 = e + (unsigned int)arithmeticShiftRight((int)f, 2);
    x1 = (unsigned int)arithmeticShiftRight((int)e, 2) - f;
    x0 = h - (unsigned int)arithmeticShiftRight((int)g, 2);

    values[0] = (int)((unsigned int)even[0] + x0);
    values[1] = (int)((unsigned int)even[1] + x1);
    values[2] = (int)((unsigned int)even[2] + x2);
    values[3] = (int)((unsigned int)even[3] + x3);
    values[4] = (int)((unsigned int)even[3] - x3);
    values[5] = (int)((unsigned int)even[2] - x2);
    values[6] = (int)((unsigned int)even[1] - x1);
    values[7] = (int)((unsigned int)even[0] - x0);
}

static void inverseTransform(const int *coefficients, int *residual,
                             unsigned int size)
{
    int block[64];
    unsigned int x;
    unsigned int y;

    for (y = 0; y < size * size; ++y)
        block[y] = coefficients[y];
    block[0] = (int)((unsigned int)block[0] + 32u);

    for (y = 0; y < size; ++y) {
        if (size == 4)
            inverse4(&block[y * size]);
        else
            inverse8(&block[y * size]);
    }

    for (y = 0; y < size; ++y) {
        for (x = y + 1; x < size; ++x) {
            int value = block[y * size + x];
            block[y * size + x] = block[x * size + y];
            block[x * size + y] = value;
        }
    }

    for (y = 0; y < size; ++y) {
        if (size == 4)
            inverse4(&block[y * size]);
        else
            inverse8(&block[y * size]);
    }

    for (y = 0; y < size * size; ++y)
        residual[y] = arithmeticShiftRight(block[y], 6);
}

static unsigned char clipByte(int value)
{
    if (value < 0)
        return 0;
    if (value > 255)
        return 255;
    return (unsigned char)value;
}

static unsigned int clip5(int value)
{
    if (value < 0)
        return 0;
    if (value > 255)
        return 31;
    return (unsigned int)value >> 3;
}

static void addResidual(unsigned char *destination, unsigned int stride,
                        const int *coefficients, unsigned int size)
{
    int residual[64];
    unsigned int x;
    unsigned int y;

    inverseTransform(coefficients, residual, size);
    for (y = 0; y < size; ++y) {
        for (x = 0; x < size; ++x) {
            unsigned int offset = y * stride + x;
            destination[offset] = clipByte((int)destination[offset] +
                                           residual[y * size + x]);
        }
    }
}

struct PackedRunLevel {
    unsigned int run;
    unsigned int level;
    bool last;
    bool negative;
};

static bool readPackedRunLevel(WordBitReader &reader,
                               const unsigned short lookup[4096],
                               PackedRunLevel &decoded)
{
    unsigned int prefix;
    unsigned int consumedValue;
    unsigned int packed;
    unsigned int consumed;

    if (!reader.peekBits(12, prefix))
        return false;
    packed = lookup[prefix];
    consumed = packed & 0xfu;
    decoded.level = (packed >> 4) & 0x1fu;
    decoded.run = (packed >> 9) & 0x3fu;
    decoded.last = ((packed >> 15) & 1u) != 0;
    if (consumed == 0 || decoded.level == 0)
        return false;
    if (!reader.readBits(consumed, consumedValue))
        return false;
    decoded.negative = (consumedValue & 1u) != 0;
    return true;
}

struct IntraContext {
    unsigned char *frame;
    unsigned int width;
    unsigned int height;
    unsigned int stride;
    unsigned int blockX;
    unsigned int blockY;
    unsigned int size;
};

static unsigned int clipCoordinate(int value, unsigned int limit)
{
    if (value < 0)
        return 0;
    if ((unsigned int)value >= limit)
        return limit - 1;
    return (unsigned int)value;
}

static unsigned char intraSample(const IntraContext &context, int x, int y)
{
    int sampleX = x;
    int sampleY = y;
    unsigned int absoluteX;
    unsigned int absoluteY;

    if (x == -1 && y >= (int)context.size) {
        sampleY = (int)context.size - 1;
    } else if (x >= -1 && y >= -1) {
        /* The ordinary neighbouring sample needs no remapping. */
    } else if (x == -1 && y == -2) {
        sampleX = 0;
        sampleY = -1;
    } else if (x == -2 && y == -1) {
        sampleX = -1;
        sampleY = 0;
    }
    absoluteX = clipCoordinate((int)context.blockX + sampleX, context.width);
    absoluteY = clipCoordinate((int)context.blockY + sampleY, context.height);
    return context.frame[absoluteY * context.stride + absoluteX];
}

static unsigned char intraHalf(int a, int b)
{
    return (unsigned char)((a + b + 1) / 2);
}

static unsigned char intraHalf3(int a, int b, int c)
{
    return (unsigned char)((a + 2 * b + c + 2) / 4);
}

static unsigned char directionalIntraSample(const IntraContext &context,
                                            unsigned int mode,
                                            int x, int y)
{
    int edge;
    int center;
    int sideA;
    int sideB;

    if (mode == 0)
        return intraSample(context, x, y - 1);
    if (mode == 1)
        return intraSample(context, x - 1, y);
    if (mode == 4) {
        edge = y + x / 2;
        if ((x & 1) == 0)
            return intraHalf(intraSample(context, -1, edge),
                             intraSample(context, -1, edge + 1));
        return intraHalf3(intraSample(context, -1, edge),
                          intraSample(context, -1, edge + 1),
                          intraSample(context, -1, edge + 2));
    }
    if (mode == 5) {
        if (x == 0)
            return intraHalf(intraSample(context, -1, y - 1),
                             intraSample(context, -1, y));
        if (y == 0)
            return intraHalf3(intraSample(context, x - 3, -1),
                              intraSample(context, x - 2, -1),
                              intraSample(context, x - 1, -1));
        if (x == 1)
            return intraHalf3(intraSample(context, -1, y - 2),
                              intraSample(context, -1, y - 1),
                              intraSample(context, -1, y));
        return intraSample(context, x - 2, y - 1);
    }
    if (mode == 6) {
        if (y == 0)
            return intraHalf(intraSample(context, x - 1, -1),
                             intraSample(context, x, -1));
        if (x == 0)
            return intraHalf3(intraSample(context, -1, y - 3),
                              intraSample(context, -1, y - 2),
                              intraSample(context, -1, y - 1));
        if (y == 1)
            return intraHalf3(intraSample(context, x - 2, -1),
                              intraSample(context, x - 1, -1),
                              intraSample(context, x, -1));
        return intraSample(context, x - 1, y - 2);
    }
    if (mode == 7) {
        center = intraSample(context, x - 1, y - 1);
        if (x != 0 && y != 0)
            return (unsigned char)center;
        sideA = x == 0 ? intraSample(context, -1, y)
                       : intraSample(context, x - 2, -1);
        sideB = y == 0 ? intraSample(context, x, -1)
                       : intraSample(context, -1, y - 2);
        return intraHalf3(sideA, center, sideB);
    }
    if (mode == 8) {
        if (y == 0)
            return intraHalf(intraSample(context, x, -1),
                             intraSample(context, x + 1, -1));
        if (y == 1)
            return intraHalf3(intraSample(context, x, -1),
                              intraSample(context, x + 1, -1),
                              intraSample(context, x + 2, -1));
        if (x < (int)context.size - 1)
            return intraSample(context, x + 1, y - 2);
        edge = y / 2 + (int)context.size - 1;
        if ((y & 1) == 0)
            return intraHalf(intraSample(context, edge, -1),
                             intraSample(context, edge + 1, -1));
        return intraHalf3(intraSample(context, edge, -1),
                          intraSample(context, edge + 1, -1),
                          intraSample(context, edge + 2, -1));
    }
    return 0;
}

static int adjustPlaneValue(int value, unsigned int size)
{
    return size == 16 ? arithmeticShiftRight(value + 1, 1) : value;
}

static bool decodePrefixMode(WordBitReader &reader,
                             const unsigned char *prefixTable,
                             unsigned int prefixBits,
                             const unsigned char lengths[10],
                             unsigned int &mode)
{
    unsigned int prefix;
    unsigned int consumed;

    if (!reader.peekBits(prefixBits, prefix))
        return false;
    mode = prefixTable[prefix];
    if (mode >= 10 || lengths[mode] == 0)
        return false;
    return reader.readBits(lengths[mode], consumed);
}

static void clearPlane(unsigned char *plane, unsigned int width,
                       unsigned int height, unsigned int stride)
{
    unsigned int x;
    unsigned int y;

    for (y = 0; y < height; ++y) {
        for (x = 0; x < width; ++x)
            plane[y * stride + x] = 0;
    }
}

static bool validFrameArguments(const unsigned char *bitstream,
                                unsigned int width,
                                unsigned int height,
                                const DecoderFrameBuffer &output)
{
    unsigned int chromaWidth = width / 2;

    return bitstream != 0 && width != 0 && height != 0 &&
           (width & 15u) == 0 && (height & 15u) == 0 &&
           output.luma != 0 && output.chromaFirst != 0 &&
           output.chromaSecond != 0 && output.lumaStride >= width &&
           output.chromaStride >= chromaWidth;
}

static bool decodeCoefficientBlock(WordBitReader &reader,
                                   const CoefficientTable &table,
                                   const unsigned int *quantScan,
                                   unsigned int coefficientCount,
                                   int coefficients[64])
{
    RunLevelSymbol symbols[64];
    unsigned int count = 0;

    if (table.lookup == 0 || table.residue == 0 || quantScan == 0 ||
        (coefficientCount != 16 && coefficientCount != 64))
        return false;
    while (count < coefficientCount) {
        if (!decodeRunLevelSymbol(reader, table.lookup, table.residue,
                                  symbols[count]))
            return false;
        ++count;
        if (symbols[count - 1].last)
            return placeRunLevelCoefficients(symbols, count, quantScan,
                                             coefficientCount, coefficients);
    }
    return false;
}

static bool addCoefficientBlock(WordBitReader &reader,
                                unsigned char *plane,
                                unsigned int stride,
                                unsigned int blockX,
                                unsigned int blockY,
                                unsigned int size,
                                const CoefficientTable &table,
                                const unsigned int *quantScan)
{
    int coefficients[64];

    if (!decodeCoefficientBlock(reader, table, quantScan, size * size,
                                coefficients))
        return false;
    addResidual(plane + blockY * stride + blockX, stride, coefficients, size);
    return true;
}

static bool predictIntra(WordBitReader &reader,
                         unsigned char *plane,
                         unsigned int width,
                         unsigned int height,
                         unsigned int stride,
                         unsigned int blockX,
                         unsigned int blockY,
                         unsigned int size,
                         unsigned int mode)
{
    int planeDelta = 0;

    if (mode == 9)
        return true;
    if (mode > 8)
        return false;
    if (mode == 2 && !reader.readSignedExpGolomb(planeDelta))
        return false;
    return predictIntraBlock(plane, width, height, stride, blockX, blockY,
                             size, mode, planeDelta);
}

static bool processIFrameBlock(WordBitReader &reader,
                               unsigned char *plane,
                               unsigned int width,
                               unsigned int height,
                               unsigned int stride,
                               unsigned int blockX,
                               unsigned int blockY,
                               int mode,
                               bool hasCoefficients,
                               unsigned char predictionModes[40],
                               const CoefficientTable &table,
                               const unsigned int quantScan8[64],
                               const unsigned int quantScan4[16])
{
    unsigned int decodedMode;
    unsigned int partition;
    unsigned int flags;
    unsigned int localX;
    unsigned int localY;

    if (!hasCoefficients) {
        if (mode < 0) {
            if (!decodePredictedIntraMode(reader, predictionModes, blockX,
                                          blockY, 8, decodedMode))
                return false;
            mode = (int)decodedMode;
        }
        return predictIntra(reader, plane, width, height, stride, blockX,
                            blockY, 8, (unsigned int)mode);
    }

    if (!reader.readUnsignedExpGolomb(partition) || partition > 16)
        return false;
    if (partition == 0) {
        if (mode < 0) {
            if (!decodePredictedIntraMode(reader, predictionModes, blockX,
                                          blockY, 8, decodedMode))
                return false;
            mode = (int)decodedMode;
        }
        return predictIntra(reader, plane, width, height, stride, blockX,
                            blockY, 8, (unsigned int)mode) &&
               addCoefficientBlock(reader, plane, stride, blockX, blockY, 8,
                                   table, quantScan8);
    }

    flags = kBlock4x4CoefficientMasks[partition - 1];
    for (localY = 0; localY < 8; localY += 4) {
        for (localX = 0; localX < 8; localX += 4) {
            int submode = mode;
            if (submode < 0) {
                if (!decodePredictedIntraMode(reader, predictionModes,
                                              blockX + localX,
                                              blockY + localY, 4,
                                              decodedMode))
                    return false;
                submode = (int)decodedMode;
            }
            if (!predictIntra(reader, plane, width, height, stride,
                              blockX + localX, blockY + localY, 4,
                              (unsigned int)submode))
                return false;
            if ((flags & 1u) != 0 &&
                !addCoefficientBlock(reader, plane, stride,
                                     blockX + localX, blockY + localY, 4,
                                     table, quantScan4))
                return false;
            flags >>= 1;
        }
    }
    return true;
}

static bool decodeIntraMacroblock(WordBitReader &reader,
                                  const DecoderFrameBuffer &output,
                                  unsigned int width,
                                  unsigned int height,
                                  unsigned int macroblockX,
                                  unsigned int macroblockY,
                                  bool predictedModes,
                                  unsigned char predictionModes[40],
                                  const CoefficientTable &table,
                                  const unsigned int quantScan8[64],
                                  const unsigned int quantScan4[16])
{
    unsigned int flagsIndex;
    unsigned int flags;
    unsigned int lumaMode;
    unsigned int chromaMode;
    unsigned int localX;
    unsigned int localY;
    unsigned int plane;
    unsigned int chromaWidth = width / 2;
    unsigned int chromaHeight = height / 2;
    unsigned char *chromaPlanes[2];
    int sharedLumaMode;

    if (!reader.readUnsignedExpGolomb(flagsIndex) || flagsIndex >= 64)
        return false;
    flags = kBlock8x8CoefficientMasks[flagsIndex];
    sharedLumaMode = -1;
    if (!predictedModes) {
        if (!reader.readBits(3, lumaMode))
            return false;
        sharedLumaMode = (int)lumaMode;
        if (lumaMode == 2) {
            if (!predictIntra(reader, output.luma, width, height,
                              output.lumaStride, macroblockX, macroblockY, 16,
                              lumaMode))
                return false;
            sharedLumaMode = 9;
        }
    }
    for (localY = 0; localY < 16; localY += 8) {
        for (localX = 0; localX < 16; localX += 8) {
            if (!processIFrameBlock(reader, output.luma, width, height,
                                    output.lumaStride,
                                    macroblockX + localX,
                                    macroblockY + localY, sharedLumaMode,
                                    (flags & 1u) != 0, predictionModes, table,
                                    quantScan8, quantScan4))
                return false;
            flags >>= 1;
        }
    }

    if (!reader.readBits(3, chromaMode))
        return false;
    chromaPlanes[0] = output.chromaFirst;
    chromaPlanes[1] = output.chromaSecond;
    if (chromaMode == 2) {
        for (plane = 0; plane < 2; ++plane) {
            if (!predictIntra(reader, chromaPlanes[plane], chromaWidth,
                              chromaHeight, output.chromaStride,
                              macroblockX / 2, macroblockY / 2, 8,
                              chromaMode))
                return false;
        }
        chromaMode = 9;
    }
    for (plane = 0; plane < 2; ++plane) {
        if (!processIFrameBlock(reader, chromaPlanes[plane], chromaWidth,
                                chromaHeight, output.chromaStride,
                                macroblockX / 2, macroblockY / 2,
                                (int)chromaMode, (flags & 1u) != 0,
                                predictionModes, table, quantScan8,
                                quantScan4))
            return false;
        flags >>= 1;
    }
    return true;
}

static bool addPFrameCoefficients(WordBitReader &reader,
                                  unsigned char *plane,
                                  unsigned int stride,
                                  unsigned int blockX,
                                  unsigned int blockY,
                                  const CoefficientTable &table,
                                  const unsigned int quantScan8[64],
                                  const unsigned int quantScan4[16])
{
    unsigned int partition;
    unsigned int flags;
    unsigned int localX;
    unsigned int localY;

    if (!reader.readUnsignedExpGolomb(partition))
        return false;
    if (partition == 0)
        return addCoefficientBlock(reader, plane, stride, blockX, blockY, 8,
                                   table, quantScan8);
    if (partition >= 16)
        return false;
    flags = kPFrameBlock4x4CoefficientMasks[partition];
    for (localY = 0; localY < 8; localY += 4) {
        for (localX = 0; localX < 8; localX += 4) {
            if ((flags & 1u) != 0 &&
                !addCoefficientBlock(reader, plane, stride,
                                     blockX + localX, blockY + localY, 4,
                                     table, quantScan4))
                return false;
            flags >>= 1;
        }
    }
    return true;
}

static int motionSizeIndex(unsigned int size)
{
    if (size == 16)
        return 0;
    if (size == 8)
        return 1;
    if (size == 4)
        return 2;
    if (size == 2)
        return 3;
    return -1;
}

static bool motionContextCodebook(unsigned int width, unsigned int height,
                                  InlineModeCodebook &codebook)
{
    static const InlineModeCodebook kMotionContexts[16] = {
        ModePFrameMacroblock, ModeMotion16, ModeMotion8x16, ModeIntra16,
        ModeMotion8x8, ModeMotion8x8Alt, ModePredictedC, ModePredictedF,
        ModeMotion16x4, ModePredictedA, ModePredictedD, ModePredictedG,
        ModeMotion16x2, ModePredictedB, ModePredictedE, ModePredictedH,
    };
    int widthIndex = motionSizeIndex(width);
    int heightIndex = motionSizeIndex(height);

    if (widthIndex < 0 || heightIndex < 0)
        return false;
    codebook = kMotionContexts[heightIndex * 4 + widthIndex];
    return true;
}

static bool predictMotionRecursive(WordBitReader &reader,
                                   unsigned int mode,
                                   unsigned int blockWidth,
                                   unsigned int blockHeight,
                                   unsigned int blockX,
                                   unsigned int blockY,
                                   unsigned int motionSlot,
                                   MotionVector *motion,
                                   const DecoderReferenceFrame *histories,
                                   unsigned int historyCount,
                                   const DecoderFrameBuffer &output,
                                   unsigned int frameWidth,
                                   unsigned int frameHeight)
{
    MotionVector vector;
    MotionVector chromaVector;
    const DecoderReferenceFrame *reference;
    unsigned int historyIndex;
    unsigned int splitX;
    unsigned int splitY;
    unsigned int childWidth;
    unsigned int childHeight;
    unsigned int child;
    unsigned int childMode;
    InlineModeCodebook codebook;

    if (mode <= 5) {
        vector = motion[0];
        if (mode > 0 && !decodePredictedMotion(reader, vector, vector))
            return false;
        motion[motionSlot] = vector;
        historyIndex = (mode > 0 ? mode : 1) - 1;
        if (historyIndex >= historyCount)
            return false;
        reference = &histories[historyIndex];
        if (reference->luma == 0 || reference->chromaFirst == 0 ||
            reference->chromaSecond == 0 ||
            reference->lumaStride < frameWidth ||
            reference->chromaStride < frameWidth / 2)
            return false;
        if (!compensateMotionBlock(reference->luma, output.luma,
                                   frameWidth, frameHeight,
                                   reference->lumaStride, output.lumaStride,
                                   blockX, blockY, blockWidth, blockHeight,
                                   vector))
            return false;
        chromaVector.x = arithmeticShiftRight(vector.x, 1);
        chromaVector.y = arithmeticShiftRight(vector.y, 1);
        if (!compensateMotionBlock(reference->chromaFirst,
                                   output.chromaFirst, frameWidth / 2,
                                   frameHeight / 2, reference->chromaStride,
                                   output.chromaStride, blockX / 2, blockY / 2,
                                   blockWidth / 2, blockHeight / 2,
                                   chromaVector) ||
            !compensateMotionBlock(reference->chromaSecond,
                                   output.chromaSecond, frameWidth / 2,
                                   frameHeight / 2, reference->chromaStride,
                                   output.chromaStride, blockX / 2, blockY / 2,
                                   blockWidth / 2, blockHeight / 2,
                                   chromaVector))
            return false;
        return true;
    }

    if (mode != 8 && mode != 9)
        return false;
    splitX = mode == 8 ? 0 : blockWidth / 2;
    splitY = mode == 8 ? blockHeight / 2 : 0;
    childWidth = blockWidth - splitX;
    childHeight = blockHeight - splitY;
    if (!motionContextCodebook(childWidth, childHeight, codebook))
        return false;
    for (child = 0; child < 2; ++child) {
        if (!decodeInlineMode(reader, codebook, childMode) ||
            !predictMotionRecursive(reader, childMode, childWidth, childHeight,
                                    blockX + child * splitX,
                                    blockY + child * splitY, motionSlot,
                                    motion, histories, historyCount, output,
                                    frameWidth, frameHeight))
            return false;
    }
    return true;
}

} // namespace

WordBitReader::WordBitReader(const unsigned char *data, unsigned int sizeBytes,
                             unsigned int zeroPaddingBytes)
    : data_(data), sizeBytes_(sizeBytes), zeroPaddingBytes_(zeroPaddingBytes),
      bitPosition_(0)
{
}

unsigned int WordBitReader::bitPosition() const
{
    return bitPosition_;
}

bool WordBitReader::readBit(unsigned int &value)
{
    unsigned int wordOffset = (bitPosition_ >> 4) << 1;
    unsigned int bitInWord = bitPosition_ & 15u;
    unsigned int word;

    if (data_ == 0 || wordOffset + 1 >= sizeBytes_ + zeroPaddingBytes_)
        return false;
    word = wordOffset < sizeBytes_ ? (unsigned int)data_[wordOffset] : 0;
    if (wordOffset + 1 < sizeBytes_)
        word |= (unsigned int)data_[wordOffset + 1] << 8;
    value = (word >> (15u - bitInWord)) & 1u;
    ++bitPosition_;
    return true;
}

bool WordBitReader::readBits(unsigned int count, unsigned int &value)
{
    unsigned int start = bitPosition_;
    unsigned int bit;
    unsigned int i;

    if (count > 32)
        return false;
    value = 0;
    for (i = 0; i < count; ++i) {
        if (!readBit(bit)) {
            bitPosition_ = start;
            return false;
        }
        value = (value << 1) | bit;
    }
    return true;
}

bool WordBitReader::peekBits(unsigned int count, unsigned int &value)
{
    unsigned int start = bitPosition_;
    bool ok = readBits(count, value);
    bitPosition_ = start;
    return ok;
}

bool WordBitReader::readUnsignedExpGolomb(unsigned int &value)
{
    unsigned int start = bitPosition_;
    unsigned int zeros = 0;
    unsigned int bit;
    unsigned int suffix;

    while (true) {
        if (!readBit(bit)) {
            bitPosition_ = start;
            return false;
        }
        if (bit != 0)
            break;
        ++zeros;
        if (zeros > 31) {
            bitPosition_ = start;
            return false;
        }
    }
    if (!readBits(zeros, suffix)) {
        bitPosition_ = start;
        return false;
    }
    value = ((1u << zeros) - 1u) + suffix;
    return true;
}

bool WordBitReader::readSignedExpGolomb(int &value)
{
    unsigned int code;
    if (!readUnsignedExpGolomb(code))
        return false;
    if ((code & 1u) != 0)
        value = (int)((code + 1u) >> 1);
    else
        value = -(int)(code >> 1);
    return true;
}

QuantizedCoefficient unpackQuantScan(unsigned int entry, int level)
{
    QuantizedCoefficient result;
    result.index = entry & 0xffu;
    result.value = (int)(signed short)(entry >> 8) * level;
    return result;
}

bool buildQuantScanTables(unsigned int quantizer,
                          unsigned int quantScan8x8[64],
                          unsigned int quantScan4x4[16])
{
    unsigned int row;
    unsigned int shift;
    unsigned int i;

    if (quantizer < 12 || quantizer > 53)
        return false;

    row = quantizer % 6;
    shift = quantizer / 6;
    for (i = 0; i < 16; ++i) {
        quantScan4x4[i] =
            ((unsigned int)kQuant4x4[row][i] << (shift + 8)) |
            (unsigned int)kZigzag4x4[i];
    }
    for (i = 0; i < 64; ++i) {
        quantScan8x8[i] =
            ((unsigned int)kQuant8x8[row][i] << (shift + 6)) |
            (unsigned int)kZigzag8x8[i];
    }
    return true;
}

bool decodeFrameHeader(WordBitReader &reader,
                       unsigned int previousQuantizer,
                       bool previousFormatVariant,
                       FrameHeader &header)
{
    unsigned int bit;
    unsigned int quantizer;
    int delta;

    if (!reader.readBit(bit))
        return false;
    header.intra = bit != 0;
    if (header.intra) {
        if (!reader.readBit(bit))
            return false;
        header.formatVariant = bit != 0;
        if (!reader.readBit(header.coefficientTableVariant))
            return false;
        if (!reader.readBits(6, quantizer))
            return false;
    } else {
        header.formatVariant = previousFormatVariant;
        header.coefficientTableVariant = 0;
        if (!reader.readSignedExpGolomb(delta))
            return false;
        quantizer = (unsigned int)((int)previousQuantizer + delta);
    }
    if (quantizer < 12 || quantizer > 53)
        return false;
    header.quantizer = quantizer;
    return true;
}

static int medianComponent(int a, int b, int c)
{
    int low;
    int high;

    if (b < a) {
        low = b;
        high = a;
    } else {
        low = a;
        high = b;
    }
    if (c < high)
        high = c;
    if (high < low)
        high = low;
    return high;
}

MotionVector medianMotionVector(const MotionVector &left,
                                const MotionVector &upperLeft,
                                const MotionVector &upper)
{
    MotionVector prediction;
    prediction.x = medianComponent(left.x, upperLeft.x, upper.x);
    prediction.y = medianComponent(left.y, upperLeft.y, upper.y);
    return prediction;
}

bool decodePredictedMotion(WordBitReader &reader,
                           const MotionVector &prediction,
                           MotionVector &motion)
{
    int deltaX;
    int deltaY;

    if (!reader.readSignedExpGolomb(deltaX) ||
        !reader.readSignedExpGolomb(deltaY))
        return false;
    motion.x = (int)((unsigned int)prediction.x + (unsigned int)deltaX);
    motion.y = (int)((unsigned int)prediction.y + (unsigned int)deltaY);
    return true;
}

void resetPredictionBorders(unsigned char predictionModes[40])
{
    predictionModes[1] = 9;
    predictionModes[2] = 9;
    predictionModes[3] = 9;
    predictionModes[4] = 9;
    predictionModes[8] = 9;
    predictionModes[16] = 9;
    predictionModes[24] = 9;
    predictionModes[32] = 9;
}

bool decodePredictedIntraMode(WordBitReader &reader,
                              unsigned char predictionModes[40],
                              unsigned int blockX,
                              unsigned int blockY,
                              unsigned int size,
                              unsigned int &mode)
{
    unsigned int index;
    unsigned int left;
    unsigned int upper;
    unsigned int reuse;
    unsigned int alternative;

    if (predictionModes == 0 || (size != 4 && size != 8))
        return false;
    index = (blockY & 0xcu) | ((blockX / 4u) % 4u);
    left = predictionModes[index];
    upper = index % 4u == 0 ? 9u : predictionModes[index + 3u];
    mode = left < upper ? left : upper;
    if (mode == 9u)
        mode = 3u;
    if (!reader.readBit(reuse))
        return false;
    if (reuse == 0) {
        if (!reader.readBits(3, alternative))
            return false;
        mode = alternative + (alternative >= mode ? 1u : 0u);
    }
    predictionModes[index + 4u] = (unsigned char)mode;
    if (size == 8) {
        predictionModes[index + 5u] = (unsigned char)mode;
        predictionModes[index + 8u] = (unsigned char)mode;
        predictionModes[index + 9u] = (unsigned char)mode;
    }
    return true;
}

bool decodePFrameMacroblockMode(WordBitReader &reader, unsigned int &mode)
{
    return decodeInlineMode(reader, ModePFrameMacroblock, mode);
}

bool decodeMotion16Mode(WordBitReader &reader, unsigned int &mode)
{
    return decodeInlineMode(reader, ModeMotion16, mode);
}

bool decodeMotion8x16Mode(WordBitReader &reader, unsigned int &mode)
{
    return decodeInlineMode(reader, ModeMotion8x16, mode);
}

bool decodeIntra16Mode(WordBitReader &reader, unsigned int &mode)
{
    return decodeInlineMode(reader, ModeIntra16, mode);
}

bool decodeInlineMode(WordBitReader &reader,
                      InlineModeCodebook codebook,
                      unsigned int &mode)
{
    if ((unsigned int)codebook >= (unsigned int)ModeCodebookCount)
        return false;
    const ModeCodebookDefinition &definition = kModeCodebooks[codebook];
    return decodePrefixMode(reader, definition.prefix, definition.prefixBits,
                            definition.lengths, mode);
}

bool predictIntraBlock(unsigned char *frame,
                       unsigned int width,
                       unsigned int height,
                       unsigned int stride,
                       unsigned int blockX,
                       unsigned int blockY,
                       unsigned int size,
                       unsigned int mode,
                       int planeDelta)
{
    IntraContext context;
    unsigned int x;
    unsigned int y;

    if (frame == 0 || width == 0 || height == 0 || stride < width)
        return false;
    if (size != 4 && size != 8 && size != 16)
        return false;
    if (mode > 8 || blockX + size > width || blockY + size > height)
        return false;

    context.frame = frame;
    context.width = width;
    context.height = height;
    context.stride = stride;
    context.blockX = blockX;
    context.blockY = blockY;
    context.size = size;

    if (mode == 2) {
        int top[16];
        int left[16];
        int horizontal[16];
        int vertical[16];
        int bottommost;
        int rightmost;
        int average;
        int slopeX;
        int slopeY;
        unsigned int shift;

        if (planeDelta < -(1 << 16))
            planeDelta = -(1 << 16);
        if (planeDelta > (1 << 16))
            planeDelta = 1 << 16;
        bottommost = frame[(blockY + size - 1) * stride +
                           (blockX == 0 ? 0 : blockX - 1)];
        rightmost = frame[(blockY == 0 ? 0 : blockY - 1) * stride +
                          blockX + size - 1];
        average = (bottommost + rightmost + 1) / 2 + 2 * planeDelta;
        slopeX = adjustPlaneValue(average - bottommost, size);
        slopeY = adjustPlaneValue(average - rightmost, size);
        shift = adjustPlaneValue((int)size, size) == 8 ? 3u : 2u;

        for (x = 0; x < size; ++x) {
            top[x] = frame[(blockY == 0 ? 0 : blockY - 1) * stride + blockX + x];
            horizontal[x] = adjustPlaneValue(
                ((bottommost - top[x]) << shift) + slopeX * (int)(x + 1),
                size);
        }
        for (y = 0; y < size; ++y) {
            left[y] = frame[(blockY + y) * stride +
                            (blockX == 0 ? 0 : blockX - 1)];
            vertical[y] = adjustPlaneValue(
                ((rightmost - left[y]) << shift) + slopeY * (int)(y + 1),
                size);
        }
        for (y = 0; y < size; ++y) {
            for (x = 0; x < size; ++x) {
                int correction = arithmeticShiftRight(
                    horizontal[x] * (int)(y + 1) +
                    vertical[y] * (int)(x + 1), 2 * shift);
                int value = (top[x] + left[y] + correction + 1) / 2;
                frame[(blockY + y) * stride + blockX + x] =
                    (unsigned char)((unsigned int)value & 0xffu);
            }
        }
        return true;
    }

    if (mode == 3) {
        unsigned int total = 0;
        unsigned int fill;
        if (blockX == 0 && blockY == 0) {
            fill = 0x80;
        } else if (blockX != 0 && blockY != 0) {
            for (y = 0; y < size; ++y)
                total += frame[(blockY + y) * stride + blockX - 1];
            for (x = 0; x < size; ++x)
                total += frame[(blockY - 1) * stride + blockX + x];
            fill = ((total * 2u) / (2u * size) + 1u) / 2u;
        } else if (blockX != 0) {
            for (y = 0; y < size; ++y)
                total += frame[(blockY + y) * stride + blockX - 1];
            fill = ((total * 2u) / size + 1u) / 2u;
        } else {
            for (x = 0; x < size; ++x)
                total += frame[(blockY - 1) * stride + blockX + x];
            fill = ((total * 2u) / size + 1u) / 2u;
        }
        for (y = 0; y < size; ++y)
            for (x = 0; x < size; ++x)
                frame[(blockY + y) * stride + blockX + x] =
                    (unsigned char)fill;
        return true;
    }

    for (y = 0; y < size; ++y) {
        for (x = 0; x < size; ++x) {
            frame[(blockY + y) * stride + blockX + x] =
                directionalIntraSample(context, mode, (int)x, (int)y);
        }
    }
    return true;
}

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
                           const MotionVector &motion)
{
    int sourceX;
    int sourceY;
    unsigned int horizontalHalf;
    unsigned int verticalHalf;
    unsigned int x;
    unsigned int y;

    if (reference == 0 || destination == 0 ||
        frameWidth == 0 || frameHeight == 0)
        return false;
    if (referenceStride < frameWidth || destinationStride < frameWidth ||
        blockWidth == 0 || blockHeight == 0)
        return false;
    if (blockX + blockWidth > frameWidth ||
        blockY + blockHeight > frameHeight)
        return false;

    sourceX = (int)blockX + arithmeticShiftRight(motion.x, 1);
    sourceY = (int)blockY + arithmeticShiftRight(motion.y, 1);
    horizontalHalf = (unsigned int)motion.x & 1u;
    verticalHalf = (unsigned int)motion.y & 1u;
    if (sourceX < 0 || sourceY < 0)
        return false;
    if ((unsigned int)sourceX + blockWidth + horizontalHalf > frameWidth ||
        (unsigned int)sourceY + blockHeight + verticalHalf > frameHeight)
        return false;

    for (y = 0; y < blockHeight; ++y) {
        for (x = 0; x < blockWidth; ++x) {
            const unsigned char *upper =
                reference + ((unsigned int)sourceY + y) * referenceStride +
                (unsigned int)sourceX + x;
            unsigned int value;
            if (horizontalHalf == 0 && verticalHalf == 0) {
                value = upper[0];
            } else if (horizontalHalf != 0 && verticalHalf == 0) {
                value = ((unsigned int)upper[0] >> 1) +
                        ((unsigned int)upper[1] >> 1);
            } else if (horizontalHalf == 0) {
                value = ((unsigned int)upper[0] >> 1) +
                        ((unsigned int)upper[referenceStride] >> 1);
            } else {
                unsigned int top =
                    (((unsigned int)upper[0] >> 1) +
                     ((unsigned int)upper[1] >> 1)) >> 1;
                const unsigned char *lower = upper + referenceStride;
                unsigned int bottom =
                    (((unsigned int)lower[0] >> 1) +
                     ((unsigned int)lower[1] >> 1)) >> 1;
                value = top + bottom;
            }
            destination[(blockY + y) * destinationStride + blockX + x] =
                (unsigned char)value;
        }
    }
    return true;
}

bool decodeRunLevelSymbol(WordBitReader &reader,
                          const unsigned short lookup[4096],
                          const unsigned char residue[256],
                          RunLevelSymbol &symbol)
{
    PackedRunLevel decoded;
    unsigned int escapePrefix;
    unsigned int selector;
    unsigned int rawLevel;

    if (lookup == 0 || residue == 0)
        return false;
    if (!reader.peekBits(7, escapePrefix))
        return false;

    if (escapePrefix != 3) {
        if (!readPackedRunLevel(reader, lookup, decoded))
            return false;
        symbol.run = decoded.run;
        symbol.level = decoded.negative ? -(int)decoded.level : (int)decoded.level;
        symbol.last = decoded.last;
        return true;
    }

    if (!reader.readBits(7, escapePrefix) || !reader.readBit(selector))
        return false;
    if (selector == 0) {
        if (!readPackedRunLevel(reader, lookup, decoded))
            return false;
        decoded.level += residue[(decoded.last ? 64u : 0u) + decoded.run];
        symbol.run = decoded.run;
        symbol.level = decoded.negative ? -(int)decoded.level : (int)decoded.level;
        symbol.last = decoded.last;
        return true;
    }

    if (!reader.readBit(selector))
        return false;
    if (selector == 0) {
        if (!readPackedRunLevel(reader, lookup, decoded))
            return false;
        decoded.run +=
            residue[128u + (decoded.last ? 64u : 0u) + decoded.level];
        symbol.run = decoded.run;
        symbol.level = decoded.negative ? -(int)decoded.level : (int)decoded.level;
        symbol.last = decoded.last;
        return true;
    }

    if (!reader.readBit(selector))
        return false;
    symbol.last = selector != 0;
    if (!reader.readBits(6, symbol.run) || !reader.readBits(12, rawLevel))
        return false;
    if ((rawLevel & 0x800u) != 0)
        symbol.level = (int)(rawLevel | 0xfffff000u);
    else
        symbol.level = (int)rawLevel;
    return true;
}

bool placeRunLevelCoefficients(const RunLevelSymbol *symbols,
                               unsigned int symbolCount,
                               const unsigned int *quantScan,
                               unsigned int coefficientCount,
                               int *coefficients)
{
    unsigned int position = 0;
    unsigned int i;

    if (symbols == 0 || quantScan == 0 || coefficients == 0)
        return false;
    if (coefficientCount != 16 && coefficientCount != 64)
        return false;

    for (i = 0; i < coefficientCount; ++i)
        coefficients[i] = 0;

    for (i = 0; i < symbolCount; ++i) {
        QuantizedCoefficient coefficient;

        if (position >= coefficientCount ||
            symbols[i].run >= coefficientCount - position)
            return false;
        position += symbols[i].run;
        coefficient = unpackQuantScan(quantScan[position], symbols[i].level);
        if (coefficient.index >= coefficientCount)
            return false;
        coefficients[coefficient.index] = coefficient.value;
        ++position;
        if (symbols[i].last)
            return true;
    }
    return false;
}

void inverseTransform4x4(const int coefficients[16], int residual[16])
{
    inverseTransform(coefficients, residual, 4);
}

void inverseTransform8x8(const int coefficients[64], int residual[64])
{
    inverseTransform(coefficients, residual, 8);
}

void addResidual4x4(unsigned char *destination, unsigned int stride,
                   const int coefficients[16])
{
    addResidual(destination, stride, coefficients, 4);
}

void addResidual8x8(unsigned char *destination, unsigned int stride,
                   const int coefficients[64])
{
    addResidual(destination, stride, coefficients, 8);
}

bool decodeIFrame(const unsigned char *bitstream,
                  unsigned int sizeBytes,
                  unsigned int width,
                  unsigned int height,
                  const CoefficientTable coefficientTables[2],
                  const DecoderFrameBuffer &output,
                  DecoderFrameResult &result)
{
    WordBitReader reader(bitstream, sizeBytes, 16);
    FrameHeader header;
    unsigned int quantScan8[64];
    unsigned int quantScan4[16];
    unsigned char predictionModes[40];
    unsigned int macroblockX;
    unsigned int macroblockY;
    unsigned int predicted;
    unsigned int i;

    if (!validFrameArguments(bitstream, width, height, output) ||
        coefficientTables == 0 || coefficientTables[0].lookup == 0 ||
        coefficientTables[0].residue == 0 ||
        coefficientTables[1].lookup == 0 ||
        coefficientTables[1].residue == 0)
        return false;
    if (!decodeFrameHeader(reader, 12, false, header) || !header.intra ||
        header.coefficientTableVariant > 1 ||
        !buildQuantScanTables(header.quantizer, quantScan8, quantScan4))
        return false;

    clearPlane(output.luma, width, height, output.lumaStride);
    clearPlane(output.chromaFirst, width / 2, height / 2,
               output.chromaStride);
    clearPlane(output.chromaSecond, width / 2, height / 2,
               output.chromaStride);
    for (i = 0; i < 40; ++i)
        predictionModes[i] = 9;

    for (macroblockY = 0; macroblockY < height; macroblockY += 16) {
        for (macroblockX = 0; macroblockX < width; macroblockX += 16) {
            if (!reader.readBit(predicted) ||
                !decodeIntraMacroblock(
                    reader, output, width, height, macroblockX, macroblockY,
                    predicted != 0, predictionModes,
                    coefficientTables[header.coefficientTableVariant],
                    quantScan8, quantScan4))
                return false;
        }
    }
    result.header = header;
    result.bitsConsumed = reader.bitPosition();
    return true;
}

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
                  DecoderFrameResult &result)
{
    WordBitReader reader(bitstream, sizeBytes, 16);
    FrameHeader header;
    unsigned int quantScan8[64];
    unsigned int quantScan4[16];
    unsigned char predictionModes[40];
    unsigned char *chromaPlanes[2];
    unsigned int macroblockX;
    unsigned int macroblockY;
    unsigned int column;
    unsigned int mode;
    unsigned int flagsIndex;
    unsigned int flags;
    unsigned int localX;
    unsigned int localY;
    unsigned int plane;
    unsigned int i;
    unsigned int motionCount = width / 16 + 3;

    if (!validFrameArguments(bitstream, width, height, output) ||
        coefficientTable0.lookup == 0 || coefficientTable0.residue == 0 ||
        histories == 0 || historyCount == 0 || motionScratch == 0 ||
        motionScratchCount < motionCount)
        return false;
    if (!decodeFrameHeader(reader, previousQuantizer,
                           previousFormatVariant, header) ||
        header.intra || header.coefficientTableVariant != 0 ||
        !buildQuantScanTables(header.quantizer, quantScan8, quantScan4))
        return false;

    clearPlane(output.luma, width, height, output.lumaStride);
    clearPlane(output.chromaFirst, width / 2, height / 2,
               output.chromaStride);
    clearPlane(output.chromaSecond, width / 2, height / 2,
               output.chromaStride);
    for (i = 0; i < 40; ++i)
        predictionModes[i] = 9;
    for (i = 0; i < motionCount; ++i) {
        motionScratch[i].x = 0;
        motionScratch[i].y = 0;
    }
    chromaPlanes[0] = output.chromaFirst;
    chromaPlanes[1] = output.chromaSecond;

    for (macroblockY = 0; macroblockY < height; macroblockY += 16) {
        for (macroblockX = 0; macroblockX < width; macroblockX += 16) {
            column = macroblockX / 16;
            motionScratch[0] = medianMotionVector(motionScratch[column + 1],
                                                  motionScratch[column + 2],
                                                  motionScratch[column + 3]);
            motionScratch[column + 2].x = 0;
            motionScratch[column + 2].y = 0;
            if (!decodeInlineMode(reader, ModePFrameMacroblock, mode))
                return false;
            if (mode == 6 || mode == 7) {
                if (!decodeIntraMacroblock(reader, output, width, height,
                                           macroblockX, macroblockY,
                                           mode == 7, predictionModes,
                                           coefficientTable0, quantScan8,
                                           quantScan4))
                    return false;
                continue;
            }
            if (!predictMotionRecursive(reader, mode, 16, 16, macroblockX,
                                        macroblockY, column + 2,
                                        motionScratch, histories, historyCount,
                                        output, width, height))
                return false;
            if (!reader.readUnsignedExpGolomb(flagsIndex) || flagsIndex >= 64)
                return false;
            flags = kPFrameBlock8x8CoefficientMasks[flagsIndex];
            for (localY = 0; localY < 16; localY += 8) {
                for (localX = 0; localX < 16; localX += 8) {
                    if ((flags & 1u) != 0 &&
                        !addPFrameCoefficients(
                            reader, output.luma, output.lumaStride,
                            macroblockX + localX, macroblockY + localY,
                            coefficientTable0, quantScan8, quantScan4))
                        return false;
                    flags >>= 1;
                }
            }
            for (plane = 0; plane < 2; ++plane) {
                if ((flags & 1u) != 0 &&
                    !addPFrameCoefficients(
                        reader, chromaPlanes[plane], output.chromaStride,
                        macroblockX / 2, macroblockY / 2,
                        coefficientTable0, quantScan8, quantScan4))
                    return false;
                flags >>= 1;
            }
        }
    }
    result.header = header;
    result.bitsConsumed = reader.bitPosition();
    return true;
}

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
                 DecoderFrameResult &result)
{
    WordBitReader probe(bitstream, sizeBytes, 2);
    unsigned int intra;

    if (coefficientTables == 0 || !probe.peekBits(1, intra))
        return false;
    if (intra != 0)
        return decodeIFrame(bitstream, sizeBytes, width, height,
                            coefficientTables, output, result);
    return decodePFrame(bitstream, sizeBytes, width, height,
                        coefficientTables[0], histories, historyCount,
                        previousQuantizer, previousFormatVariant, output,
                        motionScratch, motionScratchCount, result);
}

bool convertYCoCgToRgb555(const YCoCgFrame &frame,
                          unsigned short *destination,
                          unsigned int destinationStridePixels)
{
    unsigned int x;
    unsigned int y;

    if (frame.luma == 0 || frame.chroma == 0 || destination == 0)
        return false;
    if (frame.width == 0 || frame.height == 0 ||
        (frame.width & 15u) != 0 || (frame.height & 1u) != 0)
        return false;
    if (frame.lumaStride < frame.width ||
        frame.chromaStride < 128u + frame.width / 2u ||
        destinationStridePixels < frame.width)
        return false;

    for (y = 0; y < frame.height; ++y) {
        const unsigned char *luma = frame.luma + y * frame.lumaStride;
        const unsigned char *chroma =
            frame.chroma + (y / 2u) * frame.chromaStride;
        unsigned short *output = destination + y * destinationStridePixels;

        for (x = 0; x < frame.width; ++x) {
            int sample = (int)luma[x] - (((x + y) & 1u) != 0 ? 4 : 0);
            int co = (int)chroma[x / 2u] - 128;
            int cg = (int)chroma[128u + x / 2u] - 128;
            unsigned int red = clip5(sample + co - cg);
            unsigned int green = clip5(sample + cg);
            unsigned int blue = clip5(sample - co - cg);
            output[x] = (unsigned short)(0x8000u | red |
                                         (green << 5) | (blue << 10));
        }
    }
    return true;
}

} // namespace mobiclip
} // namespace khdays
