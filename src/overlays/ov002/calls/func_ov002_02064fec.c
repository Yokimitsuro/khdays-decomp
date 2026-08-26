/*
 * Draws the entity's four-glyph emblem into the page's tile buffer.
 *
 * Four eight-by-eight glyphs are laid out two across and two down at a fixed spot
 * on the page. Their bitmaps sit consecutively in the layer's character block
 * from offset 0x2e0, so a single cursor walks all four without ever being reset.
 * Every byte carries two pixels and a per-entity mask decides which survive.
 *
 * The cursor is a plain post-increment here, unlike the single-glyph plotter next
 * door, which needs a separate tail pointer for its fourth byte: there the row
 * pointer is rebuilt per glyph, here it runs straight through.
 *
 * The masked byte is cast to u8 before the call, which is what emits the
 * truncation after each mask.
 *
 * ARM.
 */

typedef unsigned char u8;

typedef struct Ov002PageChars {
    char pad000[0x10];
    int nCharSize;
    void *pCharData;
} Ov002PageChars;

typedef struct Ov002PageLayer {
    char pad000[0x18];
    Ov002PageChars *pGlyphs;
} Ov002PageLayer;

extern Ov002PageLayer *data_ov002_0207f638;
extern const u8 data_ov002_0207e400[];

extern void func_ov002_02064d24(int nX, int nY, int nValue);

void func_ov002_02064fec(int nSelf)
{
    Ov002PageLayer *pCtx;
    u8 bMask;
    int nGlyph;
    int nLine;
    int nDrawX;
    int nDrawY;
    const u8 *pRow;

    bMask = data_ov002_0207e400[nSelf];
    pCtx = data_ov002_0207f638;
    pRow = (const u8 *)pCtx->pGlyphs->pCharData + 0x2e0;

    for (nGlyph = 0; nGlyph < 4; nGlyph++) {
        nDrawX = (nGlyph % 2) * 8;
        nDrawY = (nGlyph / 2) * 8 + 0x20;
        for (nLine = 0; nLine < 8; nLine++) {
            func_ov002_02064d24(nDrawX + 0x34, nDrawY + nLine,
                                (u8)(bMask & *pRow++));
            func_ov002_02064d24(nDrawX + 0x36, nDrawY + nLine,
                                (u8)(bMask & *pRow++));
            func_ov002_02064d24(nDrawX + 0x38, nDrawY + nLine,
                                (u8)(bMask & *pRow++));
            func_ov002_02064d24(nDrawX + 0x3a, nDrawY + nLine,
                                (u8)(bMask & *pRow++));
        }

    }
}
