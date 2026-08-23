/*
 * Ov002_StepCrawlChar - put the next character of the crawl on screen.
 *
 * A newline moves the pen down a line and back to the left margin, and runs of
 * them are taken together. Anything else is drawn where the pen is and the pen
 * moves on by the glyph's own width; a glyph the font does not know falls back
 * to the one it names for that.
 *
 * The end of the text is reported back as zero, whether it comes before or
 * after the newlines.
 *
 * ARM.
 */

typedef unsigned short u16;
typedef unsigned char u8;

typedef struct {
    char pad000[2];
    u16 wFallback;
    char pad004[4];
    u8 *pMetrics;
} Ov002FontHeader;

typedef struct {
    Ov002FontHeader *pHeader;
} Ov002Font;

typedef struct {
    char pad000[0x6f8];
    Ov002Font *pFont;
    char pad6fc[0xc4];
    u16 *pText;
    char pad7c4[0xc];
    int nIndex;
    int nPenX;
    int nPenY;
} Ov002CrawlCtx;

extern Ov002CrawlCtx *data_ov002_0207f624;

extern void func_02030194(void *pCtx, int nX, int nY, int nFlags, int nChar);
extern int func_020136d4(Ov002Font *pFont, int nChar);
extern void *func_0201371c(Ov002Font *pFont, int nGlyph);

int func_ov002_0205e9e8(void)
{
    int nRet;
    Ov002CrawlCtx *ctx;
    u16 *pText;
    int nLine;
    int nStep;
    Ov002Font *pFont;
    int nGlyph;
    u16 wChar;

    nRet = 1;
    ctx = data_ov002_0207f624;
    pFont = ctx->pFont;
    pText = ctx->pText;
    nLine = pFont->pHeader->pMetrics[1];
    wChar = pText[ctx->nIndex];

    if (wChar != 0) {
        if (wChar == 0xa) {
            nStep = nLine + 3;
            do {
                ctx->nIndex++;
                ctx->nPenX = 0;
                ctx->nPenY += nStep;
                wChar = pText[ctx->nIndex];
            } while (wChar == 0xa);
        }

        if (wChar != 0) {
            func_02030194(&ctx->pFont, ctx->nPenX, ctx->nPenY, 8, wChar);
            nGlyph = func_020136d4(pFont, pText[ctx->nIndex]);
            if (nGlyph == 0xffff) {
                nGlyph = pFont->pHeader->wFallback;
            }
            ctx->nPenX += ((signed char *)func_0201371c(pFont, nGlyph))[2];
            ctx->nIndex++;
        } else {
            nRet = 0;
        }
    } else {
        nRet = 0;
    }
    return nRet;
}
