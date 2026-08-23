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

typedef unsigned short u16;
typedef unsigned long long u64;

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
extern const char data_ov002_0207ebd4[];
extern const char data_ov002_0207ebe4[];

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *pDst, int nValue, unsigned int nSize);
extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);
extern u64 func_020031d4(void);
extern unsigned int func_02020368(u64 llValue, unsigned int nDiv, int nMode);
extern int func_02024ee8(const void *pName, int nHeap);
extern void func_02024fd4(int nRes);
extern void func_02023c60(void *pProj);

extern void func_ov002_0205f61c(void);
extern void func_ov002_020603cc(void);
extern void func_ov002_02060488(void);
extern void func_ov002_0206079c(void);
extern void func_ov002_02060c70(void);
extern void func_ov002_02061014(void);
extern void func_ov002_020613f0(void);
extern void func_ov002_020612b0(void);
extern void *func_ov002_020616a0(void);

void *func_ov002_020614d4(const void *pInit)
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

    llNow = func_020031d4();
    s->llStepStamp = llNow;
    s->llStepInterval = 0x1474;
    s->llStamp = llNow;
    s->llInterval = 0x1474;
    s->llBlinkStamp = llNow;
    s->llBlinkInterval = 0x1474;
    s->llHoldStamp = llNow;
    s->nHoldMs = func_02020368(llNow << 6, 0x82ea, 0);

    s->nHeaderFrame = 0;
    s->nCounterState = 0;
    s->nCounterPhase = s->nCounterState;
    s->nBackdropState = 0;

    s->nFileBase = func_02024ee8(data_ov002_0207ebd4, 0xe);
    s->nBackdropBase = func_02024ee8(data_ov002_0207ebe4, 0xe);
    func_02023c60(s->aCamera);

    func_ov002_0205f61c();
    func_ov002_020603cc();
    func_ov002_02060488();
    func_ov002_0206079c();
    func_ov002_02060c70();
    func_ov002_02061014();
    func_ov002_020613f0();

    func_02024fd4(s->nBackdropBase);
    func_02024fd4(s->nFileBase);
    func_ov002_020612b0();
    return func_ov002_020616a0;
}
