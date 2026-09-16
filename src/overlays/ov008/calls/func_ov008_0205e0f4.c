/* func_ov008_0205e0f4 -- Ov008_DrawRowCountDigits: write the "placed / owned"
 * count of inventory row nRow into panel surface A (+0xac), drawing on the
 * wide glyph set's scratch buffer (02050ea4) and restoring block 968c after.
 * The owned count is written right-aligned from x = 0x7d, one decimal digit
 * per step (glyph looked up in the wide font, the font's default glyph when
 * missing; x moves left by the glyph width, the column by 4), each digit in
 * colour 0xf0 at (x + 1, 16 * row + 4) with its 0xf1 shadow at (x, 16 * row
 * + 3).  When nPlaced is not negative a '/' pair goes at x = 0x71 / 0x70
 * (colours 0xf2 / 0xf3) and the spare count (owned - placed) is written the
 * same way from x = 0x70 in colours 0xf2 / 0xf3.
 * Codegen: the second digit loop reuses nX and nGlyph but has its own
 * nLeft2 / nDigit2 (fresh registers sb / r7 there); the column step precedes
 * the division in both loops so the compare follows the subtract; the
 * declaration order nY, nLeft, nDigit, nSpare, nX, pFont, nGlyph colours
 * the first loop (5040-permutation sweep).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define GLYPH_MISSING   0xffff
#define ROW_HEIGHT      16
#define OWNED_X         0x7d
#define SPARE_X         0x70
#define SLASH_X         0x71
#define DIGIT_STEP      4

typedef struct FontHeader {
    u8  pad_00[2];
    u16 nDefaultGlyph;        /* 0x02 */
} FontHeader;

typedef struct Font {
    FontHeader *pHeader;      /* 0x00 */
} Font;

typedef struct GlyphInfo {
    u8 pad_00[2];
    signed char nWidth;       /* 0x02 */
} GlyphInfo;

typedef struct TileSurface {
    void *pPixels;            /* 0x00 */
    u8  pad_04[0x3c - 4];
} TileSurface;

typedef struct Ov008MenuContext {
    u8  pad_0000[0xac];
    TileSurface panelSurfaceA; /* 0x0ac */
} Ov008MenuContext;

extern Font *func_ov008_02050ea4(void);                                   /* wide glyph set */
extern void *func_ov008_02050e74(void);                                   /* Ov008_GetCtxBlock968c */
extern u32   func_020136d4(Font *pFont, u16 nChar);                       /* glyph index of a character */
extern GlyphInfo *func_0201371c(Font *pFont, u32 nGlyph);                 /* glyph info */
extern int   func_02030194(TileSurface *pSurface, int nX, int nY, int nColour, int nGlyph); /* Obj_ForwardInnerPayload */

void func_ov008_0205e0f4(Ov008MenuContext *pCtx, int nRow, int nPlaced, int nOwned)
{
    int nY;
    int nLeft;
    u16 nDigit;
    int nSpare;
    int nX;
    Font *pFont;
    u32 nGlyph;

    nY = nRow * ROW_HEIGHT;
    nSpare = nOwned - nPlaced;
    pFont = func_ov008_02050ea4();
    pCtx->panelSurfaceA.pPixels = func_ov008_02050ea4();
    nX = OWNED_X;
    do {
        nDigit = nOwned % 10;
        nDigit += '0';
        nGlyph = func_020136d4(pFont, nDigit);
        if (nGlyph == GLYPH_MISSING) {
            nGlyph = pFont->pHeader->nDefaultGlyph;
        }
        nLeft = nX - func_0201371c(pFont, nGlyph)->nWidth;
        func_02030194(&pCtx->panelSurfaceA, nLeft + 1, nY + 4, 0xf0, nDigit);
        func_02030194(&pCtx->panelSurfaceA, nLeft, nY + 3, 0xf1, nDigit);
        nX -= DIGIT_STEP;
        nOwned /= 10;
    } while (nOwned > 0);
    if (nPlaced >= 0) {
        int nLeft2;
        u16 nDigit2;

        func_02030194(&pCtx->panelSurfaceA, SLASH_X, nY + 4, 0xf2, '/');
        func_02030194(&pCtx->panelSurfaceA, SLASH_X - 1, nY + 3, 0xf3, '/');
        nX = SPARE_X;
        do {
            nDigit2 = nSpare % 10;
            nDigit2 += '0';
            nGlyph = func_020136d4(pFont, nDigit2);
            if (nGlyph == GLYPH_MISSING) {
                nGlyph = pFont->pHeader->nDefaultGlyph;
            }
            nLeft2 = nX - func_0201371c(pFont, nGlyph)->nWidth;
            func_02030194(&pCtx->panelSurfaceA, nLeft2 + 1, nY + 4, 0xf2, nDigit2);
            func_02030194(&pCtx->panelSurfaceA, nLeft2, nY + 3, 0xf3, nDigit2);
            nX -= DIGIT_STEP;
            nSpare /= 10;
        } while (nSpare > 0);
    }
    pCtx->panelSurfaceA.pPixels = func_ov008_02050e74();
}
