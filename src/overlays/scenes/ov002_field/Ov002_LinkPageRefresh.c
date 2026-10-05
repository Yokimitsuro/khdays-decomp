/*
 * Refreshes the link page for one step of the list.
 *
 * The step's entry is fetched and its packed descriptor decides which of the
 * page's two bases the artwork comes from; the descriptor's low nine bits and
 * the chosen base, quartered and shifted into place under the top bit, make the
 * word the appender takes.
 *
 * The two arrow cues are cleared and then re-armed from where the step sits in
 * the list: the forward arrow only while a next entry exists, the back arrow
 * only while the index is not the first, and each transition plays its own cue.
 *
 * The rest lays out the page's widgets, six of them, whose kind depends on
 * whether the list holds more than one entry and whether the page carries its
 * extra pair.
 *
 * One thing here is load-bearing rather than style. The widget kind is assigned
 * in both arms of the bias branch, not once after it. Assigned after the branch
 * the compiler folds it into an immediate add and the function comes out one
 * instruction short; assigned in both arms it stays in a register across the
 * calls, which is what the original does.
 *
 * THUMB.
 */

#include "nitro/types.h"

typedef struct Ov002LinkWidget {
    char pad000[0x3c];
} Ov002LinkWidget;

typedef struct Ov002LinkPage {
    char pad000[2];
    u16 nIndex;
    int nBase4;
    int nBase8;
    char sub00c[0x18];
    int nArg;
    char pad028[8];
    int bExtra;
    Ov002LinkWidget aWidgets[7];
} Ov002LinkPage;

extern Ov002LinkPage *data_ov002_0207f9fc;

extern u32 Ov002_Res_GetEntryOffset(void *pSub, int nStep);
extern void Ov002_AppendEntry(u32 nPacked, void *pHandler, int nArg);
extern int Ov002_Ctx_FindActiveEntryByTag(int nTag);
extern void Ov002_ForwardToSubDc_3(int hEntry);
extern void Ov002_Ctx_SetTagTrackerNodeArmed_5(int hEntry, int bArmed);
extern int Ov002_ForwardToSubDc(int nId);
extern void Ov002_ForwardToSubDc_2(int hSound);
extern int Ov002_Res_GetCount(void *pSub);
extern int Ov002_Res_GetDataBlock(void *pSub);
extern int Ov002_NextStreamRecord(void *pSub);
extern int Ov002_CountTextLines(void *pRecord);
extern void Text_DrawDirectional_2(void *pWidget, int a, int b, int c, int d, int e);
extern void EnqueueObjGfxCommand(void *pWidget);
extern void *Ov002_VariadicMapForward(void *pMsg, int nKind, void *pOut, int nSize, ...);
extern void Ov002_DrawOnSurface(void *pWidget, int a, int b, int c, void *p);
extern void Ov002_LoadBackgroundSet(void);

void Ov002_LinkPageRefresh(int nStep, int nArg)
{
    Ov002LinkPage *pCtx;
    u32 nPacked;
    int nCount;
    int nSlot;
    int nKind;
    int nBias;
    char aTmp[0x20];

    pCtx = data_ov002_0207f9fc;
    pCtx->nArg = nArg;
    nPacked = Ov002_Res_GetEntryOffset(pCtx->sub00c, nStep);
    if ((nPacked & 0x10000) != 0) {
        Ov002_AppendEntry((((pCtx->nBase8 + 0x8000) & 0xfffffc) << 7)
                            | 0x80000000
                            | (nPacked & 0x1ff),
                            Ov002_LoadBackgroundSet, 0);
    } else {
        Ov002_AppendEntry((((pCtx->nBase4 + 0x8000) & 0xfffffc) << 7)
                            | 0x80000000
                            | (nPacked & 0x1ff),
                            Ov002_LoadBackgroundSet, 0);
    }

    Ov002_ForwardToSubDc_3(Ov002_Ctx_FindActiveEntryByTag(0x16));
    Ov002_ForwardToSubDc_3(Ov002_Ctx_FindActiveEntryByTag(0x15));

    nCount = Ov002_Res_GetCount(pCtx->sub00c);
    if (pCtx->nIndex + 1 < nCount) {
        Ov002_ForwardToSubDc_2(Ov002_ForwardToSubDc(0x518));
        Ov002_Ctx_SetTagTrackerNodeArmed_5(Ov002_Ctx_FindActiveEntryByTag(0x16), 1);
        Ov002_Ctx_SetTagTrackerNodeArmed_5(Ov002_Ctx_FindActiveEntryByTag(0x17), 0);
    } else {
        Ov002_ForwardToSubDc_2(Ov002_ForwardToSubDc(0x516));
        Ov002_Ctx_SetTagTrackerNodeArmed_5(Ov002_Ctx_FindActiveEntryByTag(0x16), 0);
        Ov002_Ctx_SetTagTrackerNodeArmed_5(Ov002_Ctx_FindActiveEntryByTag(0x17), 1);
    }

    if (pCtx->nIndex != 0) {
        Ov002_Ctx_SetTagTrackerNodeArmed_5(Ov002_Ctx_FindActiveEntryByTag(0x15), 1);
    } else {
        Ov002_ForwardToSubDc_2(Ov002_ForwardToSubDc(0x514));
        Ov002_Ctx_SetTagTrackerNodeArmed_5(Ov002_Ctx_FindActiveEntryByTag(0x15), 0);
    }

    Text_DrawDirectional_2(&pCtx->aWidgets[0], 0x54, 6, 2, 0x411,
                  Ov002_Res_GetDataBlock(pCtx->sub00c));
    EnqueueObjGfxCommand(&pCtx->aWidgets[0]);

    Ov002_VariadicMapForward(&pCtx->aWidgets[6], 0, aTmp, 0x10, nStep + 1,
                        Ov002_Res_GetCount(pCtx->sub00c));
    Ov002_DrawOnSurface(&pCtx->aWidgets[1], 4, 7, 2, aTmp);

    if (pCtx->bExtra != 0) {
        nBias = 5;
        nKind = 2;
    } else {
        nBias = 0;
        nKind = 2;
    }

    nSlot = Ov002_NextStreamRecord(pCtx->sub00c);
    Ov002_DrawOnSurface(&pCtx->aWidgets[2], 0,
                        (Ov002_CountTextLines((void *)nSlot) > 1 ? 0 : 5) + 4, 2,
                        (void *)nSlot);

    nSlot = Ov002_NextStreamRecord(pCtx->sub00c);
    Ov002_DrawOnSurface(&pCtx->aWidgets[3], nBias,
                        nKind + (Ov002_CountTextLines((void *)nSlot) > 1 ? 0 : 5), 2,
                        (void *)nSlot);

    if (pCtx->bExtra != 0) {
        Ov002_DrawOnSurface(&pCtx->aWidgets[4], 5, 6, 2,
                            (void *)Ov002_NextStreamRecord(pCtx->sub00c));
        Ov002_DrawOnSurface(&pCtx->aWidgets[5], 5, 2, 2,
                            (void *)Ov002_NextStreamRecord(pCtx->sub00c));
    }
}
