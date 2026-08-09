typedef signed char s8;
typedef unsigned short u16;

typedef struct NNSG2dCharCanvas NNSG2dCharCanvas;
typedef struct NNSG2dFontInformation {
    unsigned char fontType;
    s8 linefeed;
} NNSG2dFontInformation;

typedef u16 (*NNSiG2dSplitCharCallback)(const void **pos);

typedef struct NNSG2dFont {
    NNSG2dFontInformation *pRes;
    NNSiG2dSplitCharCallback cbCharSpliter;
} NNSG2dFont;

typedef struct NNSG2dTextCanvas {
    NNSG2dCharCanvas *pCanvas;
    NNSG2dFont *pFont;
    int hSpace;
    int vSpace;
} NNSG2dTextCanvas;

typedef struct NNSG2dTagCallbackInfo {
    NNSG2dTextCanvas txn;
    const void *str;
    int x;
    int y;
    int clr;
    void *cbParam;
} NNSG2dTagCallbackInfo;

typedef void (*NNSG2dTagCallback)(u16 c, NNSG2dTagCallbackInfo *cbInfo);

typedef struct NNSiG2dTextDirection {
    s8 x;
    s8 y;
} NNSiG2dTextDirection;

extern int func_02014024(NNSG2dCharCanvas *pCanvas, NNSG2dFont *pFont,
                          int x, int y, int cl, u16 c);

static inline s8 NNS_G2dFontGetLineFeed(const NNSG2dFont *pFont)
{
    return pFont->pRes->linefeed;
}

void func_020145c0(const NNSG2dTextCanvas *pTxn,
                   int x, int y, int cl, const void *txt,
                   NNSG2dTagCallback cbFunc, void *cbParam,
                   NNSiG2dTextDirection d)
{
    const void *pos;
    int linefeed;
    int charSpace;
    const NNSG2dFont *pFont;
    NNSG2dTagCallbackInfo cbInfo;
    u16 c;
    NNSiG2dSplitCharCallback getNextChar;

    int px = x;
    int py = y;

    cbInfo.txn = *pTxn;
    cbInfo.cbParam = cbParam;

    charSpace = cbInfo.txn.hSpace;
    pFont = cbInfo.txn.pFont;
    linefeed = NNS_G2dFontGetLineFeed(pFont) + cbInfo.txn.vSpace;
    pos = txt;
    getNextChar = pFont->cbCharSpliter;

    linefeed *= d.x != 0 ? d.x : -d.y;

    while ((c = getNextChar(&pos)) != 0) {
        if (c < ' ') {
            if (c == '\n') {
                if (d.x == 0) {
                    px += linefeed;
                    py = y;
                } else {
                    px = x;
                    py += linefeed;
                }
            } else {
                cbInfo.str = pos;
                cbInfo.x = px;
                cbInfo.y = py;
                cbInfo.clr = cl;

                cbFunc(c, &cbInfo);

                pos = cbInfo.str;
                px = cbInfo.x;
                py = cbInfo.y;
                cl = cbInfo.clr;

                pFont = cbInfo.txn.pFont;
                charSpace = cbInfo.txn.hSpace;
                linefeed = NNS_G2dFontGetLineFeed(pFont) + cbInfo.txn.vSpace;
                linefeed *= d.x != 0 ? d.x : -d.y;
            }

            continue;
        } else {
            const int w = func_02014024(cbInfo.txn.pCanvas,
                                       cbInfo.txn.pFont,
                                       px, py, cl, c) + charSpace;
            px += w * d.x;
            py += w * d.y;
        }
    }
}
