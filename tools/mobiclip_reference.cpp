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

} // namespace

WordBitReader::WordBitReader(const unsigned char *data, unsigned int sizeBytes)
    : data_(data), sizeBytes_(sizeBytes), bitPosition_(0)
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

    if (data_ == 0 || wordOffset + 1 >= sizeBytes_)
        return false;
    word = (unsigned int)data_[wordOffset] |
           ((unsigned int)data_[wordOffset + 1] << 8);
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

} // namespace mobiclip
} // namespace khdays
