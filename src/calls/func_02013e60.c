/* NitroSystem g2d: CharCanvas "clear area line" -- fill a pixel rectangle with a solid
 * colour across a character-mapped (tiled) surface.
 *
 * Original: libraries/g2d/src/g2d_CharCanvas.c. The two helpers below are the library's own
 * `static inline` ones (SpreadColor32, GetCharacterSize); ClearChar is func_02013900.
 *
 * The rectangle is walked one 8x8 character at a time. For every character the rectangle is
 * clipped to that character's box and the clipped sub-rectangle is handed to ClearChar, so
 * the inner call only ever sees offsets and sizes inside a single 8x8 cell.
 *
 * Addressing is by character, not by pixel: strideTiles is the destination character map's
 * width measured in CHARACTERS, so a character's base address is pixels plus its character
 * size in bytes times (charY * strideTiles + charX). pChar walks one character to the right,
 * pCharBase one character row down.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TileSurface {
    u8 *pixels;      /* raw character data */
    int widthTiles;  /* drawable area width, in characters */
    int heightTiles; /* drawable area height, in characters */
    u8 bpp;          /* bits per pixel: 4 or 8 */
    int strideTiles; /* destination character map width, in characters */
} TileSurface;

/* Bytes occupied by one 8x8 character at the surface's colour depth. */
static inline int GetCharacterSize(const TileSurface *surf)
{
    return 8 * 8 * surf->bpp / 8;
}

/* Replicate a colour index across a whole 32-bit word: nibble-wide at 4bpp, byte-wide
 * otherwise, so one store paints eight or four pixels. */
static inline u32 SpreadColor32(const TileSurface *surf, int colour)
{
    u32 val = (u32)colour;

    if (surf->bpp == 4) {
        val = (val << 4) | val;
        val |= val << 8;
        val |= val << 16;
    } else {
        val = (val << 8) | val;
        val |= val << 16;
    }

    return val;
}

/* ClearChar: fill a sub-rectangle inside one 8x8 character. */
extern void func_02013900(void *pChar, int x, int y, int w, int h, u32 cl8, int bpp);

void func_02013e60(const TileSurface *surf, int colour, int x, int y, int width, int height)
{
    int ix, iy;
    int cx, cy, cw, ch;
    const int xw = x + width;
    const int yh = y + height;
    u32 cl8;

    cl8 = SpreadColor32(surf, colour);
    {
        const int left = x & ~(8 - 1);
        const int top = y & ~(8 - 1);
        const int right = (xw + (8 - 1)) & ~(8 - 1);
        const int bottom = (yh + (8 - 1)) & ~(8 - 1);

        const int charSize = GetCharacterSize(surf);
        const int charBaseLineOffset = (int)(surf->strideTiles * charSize);
        const int bpp = surf->bpp;
        u8 *pCharBase;
        u8 *pChar;
        pCharBase = surf->pixels + ((top / 8) * surf->strideTiles + (left / 8)) * charSize;

        for (iy = top; iy < bottom; iy += 8) {
            cy = (iy < y) ? y - iy : 0;
            ch = ((yh - iy > 8) ? 8 : yh - iy) - cy;
            pChar = pCharBase;
            for (ix = left; ix < right; ix += 8) {
                cx = (ix < x) ? x - ix : 0;
                cw = ((xw - ix > 8) ? 8 : xw - ix) - cx;

                func_02013900(pChar, cx, cy, cw, ch, cl8, bpp);
                pChar += charSize;
            }

            pCharBase += charBaseLineOffset;
        }
    }
}
