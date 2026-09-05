#include "mobiclip_reference.hpp"

using namespace khdays::mobiclip;

int main()
{
    const unsigned char word[] = {0x34, 0x12};
    unsigned int value;

    WordBitReader strict(word, sizeof(word));
    if (!strict.readBits(16, value) || value != 0x1234)
        return 1;
    if (strict.readBit(value))
        return 2;

    WordBitReader padded(word, sizeof(word), 2);
    if (!padded.readBits(16, value) || value != 0x1234)
        return 3;
    if (!padded.readBits(16, value) || value != 0)
        return 4;
    if (padded.readBit(value))
        return 5;

    // P-frame header: intra=0 followed by signed Exp-Golomb +1 (010).
    const unsigned char pHeader[] = {0x00, 0x20};
    WordBitReader headerReader(pHeader, sizeof(pHeader));
    FrameHeader header;
    if (!decodeFrameHeader(headerReader, 26, false, header))
        return 6;
    if (header.intra || header.formatVariant ||
        header.coefficientTableVariant != 0 || header.quantizer != 27 ||
        headerReader.bitPosition() != 4)
        return 7;
    return 0;
}
