/*
 * Ov002_SceneCreatePanel - build the panel scene and hand back its first step.
 *
 * The scene block is taken from the root heap, cleared, and seeded with the
 * caller's starting total when one is given. All four tick pairs are stamped
 * with the current tick and given the same ten-millisecond interval - 0x1474
 * ticks, the same number as the size of the block - and the backdrop's dwell
 * time is the current tick in milliseconds.
 *
 * The two archives the widgets are cut from are opened, every widget group is
 * put back to its opening state, and both archives are closed again - the
 * widgets keep only what they copied out. The title widget is reset last.
 *
 * THUMB. The starting total is stored inside both arms of the test rather than
 * through a shared local: mwcc merges the identical tails into one store, which
 * is what leaves the second statement to materialise the field offset again.
 */

#include "nitro/types.h"

typedef struct {
    u16 wStart;
    char pad002[2];
    char aCamera[0x38];
    int nFileBase;
    int nBackdropBase;
    char pad044[0xa0];
    int nHeaderFrame;
    char pad0e8[0xc70];
    int nCounterState;
    int nCounterPhase;
    int nTotalShown;
    int nTotalTarget;
    char padd68[0x284];
    int nBackdropState;
    char padff0[0x3c];
    u64 llStepStamp;
    u64 llStepInterval;
    u64 llStamp;
    u64 llInterval;
    u64 llBlinkStamp;
    u64 llBlinkInterval;
    u64 llHoldStamp;
    unsigned int nHoldMs;
} Ov002PanelScene;

extern int data_ov002_0207f628;
extern const char gOv002UiHcntArcPath[];
extern const char gOv002UiHcntArcPath_2[];

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *pDst, int nValue, unsigned int nSize);
extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);
extern u64 OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern int Msg_OpenContainerAndReadHeader(const void *pName, int nHeap);
extern void ZeroHalfThenFree(int nRes);
extern void Projection_LoadDefaults(void *pProj);

extern void Ov002_SceneResetPanelWidgets(void);
extern void Ov002_SceneResetPanelCounters(void);
extern void Ov002_SceneResetPanelBackdrop(void);
extern void Ov002_RestartEmitters(void);
extern void Ov002_SceneResetPanelMarker(void);
extern void Ov002_SceneResetPanelHud(void);
extern void Ov002_SceneResetPanelFrame(void);
extern void Ov002_ResetTitleWidget(void);
extern void *Ov002_SceneStepPanel(void);

void *Ov002_SceneCreatePanel(const void *pInit)
{
    u64 llNow;
    Ov002PanelScene *s;

    s = NNSi_FndGetCurrentRootHeap();
    *(Ov002PanelScene **)&data_ov002_0207f628 = s;
    MI_CpuFill8(s, 0, 0x1474);

    if (pInit != 0) {
        MI_CpuCopy8(pInit, s, 2);
        s->nTotalShown = s->wStart;
    } else {
        s->nTotalShown = 0;
    }
    s->nTotalTarget = s->nTotalShown;

    llNow = OS_GetTick();
    s->llStepStamp = llNow;
    s->llStepInterval = 0x1474;
    s->llStamp = llNow;
    s->llInterval = 0x1474;
    s->llBlinkStamp = llNow;
    s->llBlinkInterval = 0x1474;
    s->llHoldStamp = llNow;
    s->nHoldMs = (unsigned int)func_02020368(llNow << 6, 0x82ea);

    s->nHeaderFrame = 0;
    s->nCounterState = 0;
    s->nCounterPhase = s->nCounterState;
    s->nBackdropState = 0;

    s->nFileBase = Msg_OpenContainerAndReadHeader(gOv002UiHcntArcPath, 0xe);
    s->nBackdropBase = Msg_OpenContainerAndReadHeader(gOv002UiHcntArcPath_2, 0xe);
    Projection_LoadDefaults(s->aCamera);

    Ov002_SceneResetPanelWidgets();
    Ov002_SceneResetPanelCounters();
    Ov002_SceneResetPanelBackdrop();
    Ov002_RestartEmitters();
    Ov002_SceneResetPanelMarker();
    Ov002_SceneResetPanelHud();
    Ov002_SceneResetPanelFrame();

    ZeroHalfThenFree(s->nBackdropBase);
    ZeroHalfThenFree(s->nFileBase);
    Ov002_ResetTitleWidget();
    return Ov002_SceneStepPanel;
}
