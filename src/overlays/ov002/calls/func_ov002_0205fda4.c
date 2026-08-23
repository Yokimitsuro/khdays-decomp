/*
 * Ov002_SceneStepPanelFlash - run the three-step flash the panel plays over its
 * counter row.
 *
 * The step counter is clamped back to 0 whenever it leaves 1..3, and nothing
 * happens while it sits at 0. Otherwise each of the three tweens that is done
 * is handed the leg of its own track for the current step: the level track
 * fades the row in and back out, the tint track brightens and drops it, and the
 * slide track carries it across. Only the level tween advances the step, so the
 * other two follow it.
 *
 * The three tweens are sampled every call, whether or not a step started, and
 * their values become the row's middle tint, its list level and its X offset.
 *
 * ARM.
 */

typedef struct {
    int nMode;
    int nDuration;
    int nFrom;
    int nTo;
    int aStart[2];
    unsigned int pad0 : 2;
    unsigned int bDone : 1;
} Ov002Tween;

typedef struct {
    int nFrom;
    int nTo;
    short nDuration;
} Ov002FxStep;

typedef struct {
    Ov002FxStep aStep[3];
} Ov002FxTrack;

typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

typedef struct {
    char pad000[0x370];
    int nRowList;
    char pad374[0x28];
    Ov002Vec3 vRowPos;
    int aRowTint[3];
    char pad3b4[0x3a0];
    Ov002Tween aFlash[4];
    int nFlashStep;
} Ov002FlashScene;

extern int data_ov002_0207f628;
extern const Ov002FxTrack data_ov002_0207e1a8;
extern const Ov002FxTrack data_ov002_0207e1cc;
extern const Ov002FxTrack data_ov002_0207e1f0;

extern void func_02035fb0(Ov002Tween *pTween, int nMode, int nFrom, int nTo,
                          int nDuration);
extern void func_02035ffc(Ov002Tween *pTween);
extern void func_0203602c(Ov002Tween *pTween, int *pOut);
extern void func_02016d10(int nList, int nValue);

void func_ov002_0205fda4(void)
{
    Ov002Vec3 v;
    Ov002FxTrack level = data_ov002_0207e1a8;
    Ov002FxTrack tint = data_ov002_0207e1cc;
    Ov002FxTrack slide = data_ov002_0207e1f0;
    int nTint = 0;
    int nLevel = 0;
    int nSlide = 0;
    int nStep;
    int nValue;
    Ov002FlashScene *s;

    s = *(Ov002FlashScene **)&data_ov002_0207f628;
    nStep = s->nFlashStep - 1;
    if ((unsigned int)nStep >= 3) {
        s->nFlashStep = 0;
    }

    if (s->nFlashStep > 0) {
        if (s->aFlash[3].bDone != 0) {
            func_02035fb0(&s->aFlash[3], 0, level.aStep[nStep].nFrom,
                          level.aStep[nStep].nTo,
                          level.aStep[nStep].nDuration);
            func_02035ffc(&s->aFlash[3]);
            s->nFlashStep++;
        }
        if (s->aFlash[2].bDone != 0) {
            func_02035fb0(&s->aFlash[2], 0, tint.aStep[nStep].nFrom,
                          tint.aStep[nStep].nTo, tint.aStep[nStep].nDuration);
            func_02035ffc(&s->aFlash[2]);
        }
        if (s->aFlash[1].bDone != 0) {
            func_02035fb0(&s->aFlash[1], 0, slide.aStep[nStep].nFrom,
                          slide.aStep[nStep].nTo,
                          slide.aStep[nStep].nDuration);
            func_02035ffc(&s->aFlash[1]);
        }
    }

    func_0203602c(&s->aFlash[2], &nTint);
    func_0203602c(&s->aFlash[3], &nLevel);
    func_0203602c(&s->aFlash[1], &nSlide);

    nValue = nTint;
    s->aRowTint[0] = 0xe66;
    s->aRowTint[1] = nValue;
    s->aRowTint[2] = 0xe66;
    func_02016d10(s->nRowList, nLevel >> 12);

    v.x = nSlide >> 12;
    v.y = 0x3520;
    v.z = -0x100000;
    s->vRowPos = v;
}
