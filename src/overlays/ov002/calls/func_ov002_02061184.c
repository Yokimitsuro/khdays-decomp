/*
 * Ov002_SceneStepPanelHud - refresh the two numbers the panel's HUD shows.
 *
 * The first is a count that is re-read every frame while it is wanted: it is
 * drawn, and a chime plays whenever it changes into the range 1..10, which is
 * where it starts to matter.
 *
 * The second is a countdown, drawn in whole seconds - rounded up, at whatever
 * frame rate the machine is set to - and then run down by however many frames
 * have passed since the last call, stopping at zero.
 *
 * ARM.
 */

typedef unsigned short u16;

typedef struct {
    char pad000[0xd8];
    int bHudDirty;
    int bHudHeld;
    char pad0e0[0x1240];
    int nTicksLeft;
    int nFrameStamp;
    u16 wLastCount;
} Ov002HudScene;

extern int data_ov002_0207f628;
extern int data_0204c058;

extern int func_02023c50(void);
extern long long func_0202060c(int nNumer, int nDenom);
extern void func_02033b24(int nBank, int nSound);

extern int func_ov002_0206dbe0(void);
extern void func_ov002_02061098(int nX, int nY, int nValue);

void func_ov002_02061184(void)
{
    Ov002HudScene *s;
    int nFps;
    unsigned int nCount;
    int nNow;
    unsigned int nDelta;

    s = *(Ov002HudScene **)&data_ov002_0207f628;
    nNow = func_02023c50();
    nDelta = nNow - s->nFrameStamp;

    if (s->bHudDirty != 0) {
        nCount = (u16)func_ov002_0206dbe0();
        func_ov002_02061098(0, 0x4f000, nCount);
        if (nCount != 0 && nCount <= 10 && nCount != s->wLastCount) {
            s->wLastCount = (u16)nCount;
            func_02033b24(0, 0x67);
        }
    }

    if (s->bHudHeld != 0) {
        switch (*(unsigned char *)&data_0204c058) {
        case 0:
            nFps = 0x1e;
            break;
        case 1:
            nFps = 0x14;
            break;
        case 2:
            nFps = 0x3c;
            break;
        }
        func_ov002_02061098(0, 0x50000,
                            (int)func_0202060c(s->nTicksLeft + nFps - 1, nFps));
        if (s->nTicksLeft > nDelta) {
            s->nTicksLeft -= nDelta;
        } else {
            s->nTicksLeft = 0;
        }
    }

    s->nFrameStamp = nNow;
}
