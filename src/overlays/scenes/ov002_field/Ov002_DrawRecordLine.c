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

#include "nitro/types.h"

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

extern char gOv002StrFmt_2[];

extern int ScriptVm_ReadOperandInt(Ov002Ctx *pCtx, void *pArg);
extern char *ByteCode_ResolveOperand(Ov002Ctx *pCtx, void *pArg);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int OS_SNPrintf(char *dst, unsigned int len, const char *fmt, ...);
extern void Ov002_SplitPath(char *pDest, const s8 *pName);
extern u32 strlen(const char *pStr);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void Utf8_ToUcs2(char *pSrc, char *pDest);
extern void Ov002_TryBeginPanelRequest(Ov002TextReq *pReq, int nValue);

void Ov002_DrawRecordLine(Ov002Ctx *pCtx, void *pArg)
{
    int hFont;
    Ov002TextReq req;
    char szText[0x100];
    u32 nSize;
    char *pWide;
    char *pOut;

    hFont = ScriptVm_ReadOperandInt(pCtx, (char *)pArg + 0x10);
    if (pCtx->pRec->szName[0] != 0) {
        OS_SPrintf(szText, gOv002StrFmt_2, pCtx->pRec->szName);
    } else {
        OS_SPrintf(szText, gOv002StrFmt_2, ByteCode_ResolveOperand(pCtx, pArg));
    }

    Ov002_SplitPath(szText, pCtx->pRec->szName);

    nSize = strlen(szText) * 2;
    pWide = NNSi_FndAllocFromDefaultExpHeap(nSize);
    pOut = NNSi_FndAllocFromDefaultExpHeap(nSize * 2);
    OS_SNPrintf(pWide, nSize, szText, pCtx->pRec->nValue);
    Utf8_ToUcs2(pWide, pOut);
    NNSi_FndFreeFromDefaultHeap(pWide);

    req.pText = pOut;
    req.n0c = 0;
    req.n08 = 0;
    req.n04 = 0;
    req.hFont = hFont;
    req.n14 = -1;
    req.n18 = 0;
    Ov002_TryBeginPanelRequest(&req, 0);

    NNSi_FndFreeFromDefaultHeap(pOut);
}
