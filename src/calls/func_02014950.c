/* Read the next nBits from a glyph bitstream, MSB first.
 *
 * The reader holds one buffered byte and a count of how many of its bits are still
 * unread. When the request fits in what is buffered, the bits are shifted out of the
 * buffer and the count is reduced. When it does not, the reader consumes the next
 * source byte, refills to 8 available bits and recurses for the remainder, then
 * splices the bits it already had above the ones the recursion returned.
 *
 * Field order follows this function itself: offset 4 is loaded with ldrsb and compared
 * against the requested count, so it is the SIGNED number of bits still available, and
 * offset 5 is loaded with ldrb and shifted right, so it is the unsigned bit buffer.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;

typedef struct NNSiG2dBitReader {
    const u8 *src;
    s8 availableBits;
    u8 bits;
} NNSiG2dBitReader;

u32 func_02014950(NNSiG2dBitReader *reader, int nBits)
{
    int availableBits = reader->availableBits;
    u8 bits = reader->bits;
    u32 value;

    if (availableBits < nBits) {
        const u8 *src = reader->src;
        int rest = nBits - availableBits;

        reader->src = src + 1;
        reader->bits = *src;
        reader->availableBits = 8;
        value = func_02014950(reader, rest) | ((u32)bits << rest);
    } else {
        value = (u32)bits >> (availableBits - nBits);
        reader->availableBits = (s8)(availableBits - nBits);
    }

    return value & (0xff >> (8 - nBits));
}
