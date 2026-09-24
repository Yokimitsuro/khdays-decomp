#pragma thumb on
/* func_0202fdac -- draw a string into a text canvas, optionally with a drop shadow, MAIN. The area
 * size is recorded in the size table data_0204c218 ({w, h} and the shadow's {w - 1, h - 1}). The
 * one-pixel shift that follows the text direction comes from the font's glyph rotation flags (+7 of its glyph
 * info): rotations 0/7 step right, 1/2 down, 3/4 left, 5/6 up. With `shadow`, the string is drawn
 * one pixel down-right in the shadow area first; then it is drawn in place. Both passes go
 * through func_020145c0 with the glyph callback func_0202fd90. */
typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef int BOOL;

typedef struct { u8 cellWidth, cellHeight; u16 cellSize; s8 baselinePos; u8 maxCharWidth, bpp, flags; } FontGlyph;
typedef struct { u8 pad00[8]; FontGlyph *pGlyph; } FontInfo;
typedef struct { FontInfo *pRes; } Font;
typedef struct { void *pCanvas; Font *pFont; } TextCanvas;

typedef struct { int w; int h; } TextSize;
typedef struct { s8 dx; s8 dy; } TextStep;

/* The size table is the function's own static: that is what gives it a second pool word for the
 * final pass's argument; the module's delinked bss keeps the symbol (tools/share_bss.py). */
/* khdays: shared-bss */
extern void func_0202fd90(void);
extern void func_020145c0(TextCanvas *tc, int x, int y, int w, const u16 *str, void (*glyphCb)(void),
                          const TextSize *size, TextStep step);

void func_0202fdac(TextCanvas *tc, int x, int y, int w, int h, const u16 *str, BOOL shadow)
{
    static TextSize data_0204c218[2];   /* sizes: text area, shadow area */

    data_0204c218[0].w = w;
    data_0204c218[0].h = h;
    data_0204c218[1].w = w - 1;
    data_0204c218[1].h = h - 1;
    if (shadow) {
        Font *font = tc->pFont;
        TextStep shadowStep = {0, 0};

        switch (font->pRes->pGlyph->flags) {
        case 0:
        case 7:
            shadowStep.dx = 1;
            break;
        case 1:
        case 2:
            shadowStep.dy = 1;
            break;
        case 3:
        case 4:
            shadowStep.dx = -1;
            break;
        case 5:
        case 6:
            shadowStep.dy = -1;
            break;
        }
        func_020145c0(tc, x + 1, y + 1, w - 1, str, func_0202fd90, &data_0204c218[1], shadowStep);
    }
    {
        Font *font = tc->pFont;
        TextStep step = {0, 0};

        switch (font->pRes->pGlyph->flags) {
        case 0:
        case 7:
            step.dx = 1;
            break;
        case 1:
        case 2:
            step.dy = 1;
            break;
        case 3:
        case 4:
            step.dx = -1;
            break;
        case 5:
        case 6:
            step.dy = -1;
            break;
        }
        func_020145c0(tc, x, y, w, str, func_0202fd90, &data_0204c218[0], step);
    }
}
