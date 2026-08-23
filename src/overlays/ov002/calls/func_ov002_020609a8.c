/*
 * Ov002_SceneStepPanelBackdrop - hold the backdrop up for its dwell time and
 * then fade it away.
 *
 * A pending refresh is applied first. The rest only runs while the backdrop is
 * in state 1, the one state where it is on screen.
 *
 * Its tween is sampled, a held tween contributing nothing. Once the last third
 * of the dwell time is reached - or something is holding the backdrop down -
 * the fade is started, once, and restarted whenever the tween runs out while
 * the fade is still owed. The widget is then drawn at whatever level the tween
 * reads.
 *
 * When the whole dwell time has passed the backdrop drops back to state 0 and
 * both flags are cleared.
 *
 * ARM.
 */

typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

typedef struct {
    char pad000[0x78];
    int nList;
    char pad07c[0x28];
    Ov002Vec3 vPos;
    int aTint[3];
    char pad0bc[0x4c];
} Ov002Widget;

typedef struct {
    int nMode;
    int nDuration;
    int nFrom;
    int nTo;
    int aStart[2];
    unsigned int pad0 : 2;
    unsigned int bHeld : 1;
} Ov002Tween;

typedef struct {
    char pad000[0xcc];
    int bDirty;
    int bFading;
    int bHeldDown;
    char pad0d8[0xce8];
    Ov002Widget backdropWidget;
    char padec8[0x108];
    Ov002Tween tweenBackdrop;
    int nBackdropState;
    char padff0[0x6c];
    u64 llHoldStamp;
    u32 nHoldMs;
} Ov002BackdropScene;

extern int data_ov002_0207f628;

extern u64 func_020031d4(void);
extern void func_02035fb0(Ov002Tween *pTween, int nMode, int nFrom, int nTo,
                          int nDuration);
extern void func_02035ffc(Ov002Tween *pTween);
extern void func_0203602c(Ov002Tween *pTween, int *pOut);
extern void func_02016d10(int nList, int nValue);

extern void func_ov002_0206030c(void);
extern void func_ov002_0205f810(void *pWidget);

void func_ov002_020609a8(void)
{
    int nLevel;
    u64 llNow;
    Ov002BackdropScene *s;
    u64 llDelta;
    u64 llFade;

    s = *(Ov002BackdropScene **)&data_ov002_0207f628;
    llNow = func_020031d4();
    llDelta = llNow - s->llHoldStamp;
    llFade = ((u64)s->nHoldMs * 0x82ea >> 6)
             - ((u64)(s->nHoldMs / 3) * 0x82ea >> 6);

    if (s->bDirty != 0) {
        func_ov002_0206030c();
        s->bDirty = 0;
    }
    if (s->nBackdropState == 0) {
        return;
    }
    if (s->nBackdropState != 1) {
        return;
    }

    if (s->tweenBackdrop.bHeld != 0) {
        nLevel = 0;
    } else {
        func_0203602c(&s->tweenBackdrop, &nLevel);
    }

    if (llDelta > llFade || s->bHeldDown != 0) {
        if (s->bFading == 0) {
            func_02035fb0(&s->tweenBackdrop, 0, 0x1f000, 0, 300);
            func_02035ffc(&s->tweenBackdrop);
            s->bFading = 1;
        }
        if (s->bFading != 0) {
            if (s->tweenBackdrop.bHeld != 0) {
                func_02035fb0(&s->tweenBackdrop, 0, 0x1f000, 0, 300);
                func_02035ffc(&s->tweenBackdrop);
            }
        }
    }

    func_02016d10(s->backdropWidget.nList, nLevel >> 12);
    func_ov002_0205f810(&s->backdropWidget);

    if (llDelta > (u64)s->nHoldMs * 0x82ea >> 6) {
        s->bFading = 0;
        s->bHeldDown = 0;
        s->nBackdropState = 0;
    }
}
