/*
 * Ov002_StartHudTimer - switch on one of the panel's two HUD numbers and give
 * it a running time.
 *
 * The caller's time is in seconds; it is turned into frames at whatever rate
 * the machine is set to. Kind 0 is the count, which also remembers what it
 * currently reads so the chime only plays on a change; kind 1 is the countdown.
 * Any other kind does nothing.
 *
 * ARM.
 */

typedef unsigned short u16;

typedef struct {
    char pad000[0xd8];
    int bHudDirty;
    int bHudHeld;
    char pad0e0[0x123c];
    int nCountTicks;
    int nTicksLeft;
    char pad1324[4];
    u16 wLastCount;
} Ov002HudScene;

extern int data_ov002_0207f628;
extern int data_0204c058;

extern int func_ov002_0206dbe0(void);

void func_ov002_02061d64(int nKind, int nSeconds)
{
    int nFps;
    Ov002HudScene *s;

    s = *(Ov002HudScene **)&data_ov002_0207f628;
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

    switch (nKind) {
    case 0:
        s->bHudDirty = 1;
        s->nCountTicks = nSeconds * nFps;
        s->wLastCount = (u16)func_ov002_0206dbe0();
        break;
    case 1:
        s->bHudHeld = 1;
        s->nTicksLeft = nSeconds * nFps;
        break;
    }
}
