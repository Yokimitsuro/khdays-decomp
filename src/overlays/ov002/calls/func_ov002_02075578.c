/*
 * Formats one record's line and hands it to the text drawer.
 *
 * The line starts from the record's own name when it has one, and from the
 * fallback the context supplies when it does not; either way the record's
 * suffix is appended. That formatted line is then used as a format itself,
 * with the record's value, into a freshly allocated buffer, widened into a
 * second one, and drawn through a request carrying the font the caller
 * resolved. Both buffers are freed on the way out.
 *
 * One thing here is load-bearing rather than style. The request's three zeroed
 * words are assigned from the highest offset down. The compiler emits them in
 * source order, and the original writes them descending.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;

typedef struct Ov002Rec {
    char pad000[0x10];
    int nValue;
    char pad014[0x490];
    s8 szName[1];
} Ov002Rec;

typedef struct Ov002Ctx {
    char pad000[0x128];
    Ov002Rec *pRec;
} Ov002Ctx;

typedef struct Ov002TextReq {
    char *pText;
    int n04;
    int n08;
    int n0c;
    int hFont;
    int n14;
    int n18;
    char pad1c[8];
} Ov002TextReq;

extern char data_ov002_0207f404[];

extern int func_02021980(Ov002Ctx *pCtx, void *pArg);
extern char *func_02021948(Ov002Ctx *pCtx, void *pArg);
extern void OS_SPrintf(char *pDest, const char *pFmt, ...);
extern void OS_SNPrintf(char *pDest, u32 nSize, const char *pFmt, ...);
extern void func_ov002_02075528(char *pDest, const s8 *pName);
extern u32 strlen(const char *pStr);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_0202fcb8(char *pSrc, char *pDest);
extern void func_ov002_02057300(Ov002TextReq *pReq);

void func_ov002_02075578(Ov002Ctx *pCtx, void *pArg)
{
    int hFont;
    Ov002TextReq req;
    char szText[0x100];
    u32 nSize;
    char *pWide;
    char *pOut;

    hFont = func_02021980(pCtx, (char *)pArg + 0x10);
    if (pCtx->pRec->szName[0] != 0) {
        OS_SPrintf(szText, data_ov002_0207f404, pCtx->pRec->szName);
    } else {
        OS_SPrintf(szText, data_ov002_0207f404, func_02021948(pCtx, pArg));
    }

    func_ov002_02075528(szText, pCtx->pRec->szName);

    nSize = strlen(szText) * 2;
    pWide = NNSi_FndAllocFromDefaultExpHeap(nSize);
    pOut = NNSi_FndAllocFromDefaultExpHeap(nSize * 2);
    OS_SNPrintf(pWide, nSize, szText, pCtx->pRec->nValue);
    func_0202fcb8(pWide, pOut);
    NNSi_FndFreeFromDefaultHeap(pWide);

    req.pText = pOut;
    req.n0c = 0;
    req.n08 = 0;
    req.n04 = 0;
    req.hFont = hFont;
    req.n14 = -1;
    req.n18 = 0;
    func_ov002_02057300(&req);

    NNSi_FndFreeFromDefaultHeap(pOut);
}
