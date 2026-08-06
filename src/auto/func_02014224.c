/* Tilemap_FillIncrementing: write a rectangle of consecutive tile indices into a BG screen.
 *
 * Each entry is the running tile number ORed with the palette number in bits 12..15, and dst
 * advances by mapW entries per row, so the rectangle can be narrower than the screen.
 *
 * Two spellings carry the whole match:
 *
 *  - `tile` must be an int. As a u16 every ++ drags a lsl/lsr #16 truncation pair into the
 *    inner loop and the function grows from 92 to 108 bytes.
 *
 *  - the palette pack must be a u16 local initialised from `(u16)(pal << 12)`. mwcc implements
 *    that 16-bit truncation as the shift pair `pal << 28` then `>> 16`, keeps the `<< 28` in
 *    the entry block and folds the `>> 16` into the ORR as a shifted operand. Writing the pair
 *    out by hand as `(u32)(pal << 28) >> 16` computes the same value but makes the invariant a
 *    source local, which takes the callee-saved register the original gives to `pal` itself,
 *    and leaves a 3-cycle register rotation that no declaration order can undo.
 */

typedef unsigned short u16;

void func_02014224(u16 *dst, int width, int height, int mapW, int tile, int pal)
{
    u16 palBits;
    int x;
    int y;
    u16 *row;

    palBits = (u16)(pal << 12);
    for (y = 0; y < height; y++) {
        row = dst;
        for (x = 0; x < width; x++) {
            *row++ = (u16)(tile++ | palBits);
        }
        dst += mapW;
    }
}
