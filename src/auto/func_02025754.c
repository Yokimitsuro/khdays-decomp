/* BitArray_SetField - write the low bitCount bits of `value` into a field at
 * bitOffset in the packed u32 bit-array at `base`, MSB-first, spanning word
 * boundaries: each word becomes (old & ~mask) | (value & mask). Twin of the
 * reader func_020256b8 (BitArray_GetField); `value` is signed (arithmetic shift).
 *
 * Codegen note: same allocation crack as the reader - walk the pointer parameter
 * in place, reuse the bitOffset parameter as the loop-carried offset (masked in
 * place, reset to 0 each pass) with a separate local n = 32 - bitOffset, and keep
 * the store as `*base = ...; base++;` so it lowers to str rX,[r0],#4.
 */
typedef unsigned int u32;
void func_02025754(u32 *base, u32 bitOffset, u32 bitCount, int value)
{
    u32 mask;
    u32 n;
    base += (int)bitOffset / 32;
    bitOffset &= 0x1f;
    if ((int)(bitOffset + bitCount) > 0x20) {
        do {
            n = 0x20 - bitOffset;
            mask = (n == 0x20) ? 0xffffffff : (1u << n) - 1;
            bitCount -= n;
            *base = (*base & ~mask) | (mask & (value >> bitCount));
            base++;
            bitOffset = 0;
        } while ((int)bitCount > 0x20);
    }
    if ((int)bitCount > 0) {
        mask = (bitCount == 0x20) ? 0xffffffff : (1u << bitCount) - 1;
        n = (0x20 - bitOffset) - bitCount;
        *base = (*base & ~(mask << n)) | ((value & mask) << n);
    }
}
