/*
 * Ov002_SceneDrawPanelCounters - draw the ten counters that ride along the
 * panel's rows.
 *
 * The shared tint and the shared depth are each either a fixed value, when the
 * tween that drives them is being held, or whatever that tween is at. The tint
 * goes to the three colour slots and the depth to the list.
 *
 * Every row then samples its own pair of tweens: the one that moves it and the
 * one that fades it. A row whose tween is held contributes nothing and, in the
 * fade case, also drops the row's standing request. A row that sampled either
 * tween is marked as needing a redraw.
 *
 * Each marked row is finally drawn digit by digit, from the most significant
 * down: the digit widget takes the row's palette, is bound to the digit (or to
 * the blank glyph once the number has run out), and is placed so the whole
 * number ends at the same right edge whatever its length.
 *
 * ARM.
 */

typedef unsigned short u16;

typedef struct {
    int aWords[6];
    unsigned int pad0 : 2;
    unsigned int bHeld : 1;
} Ov002Tween;

typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

extern int data_ov002_0207f628;

extern void func_0203602c(void *pTween, int *pOut);
extern void func_02016cd0(int nList, int nValue);
extern void func_02016d10(int nList, int nValue);
extern void func_0202afdc(void *pWidget, u16 nValue);

extern int func_ov002_020618d8(int nValue);
extern int func_ov002_02061908(int nIndex, int nValue);
extern void func_ov002_020617f8(void *pWidget, int nDigit);
extern void func_ov002_0205f810(void *pWidget);

void func_ov002_0205f9a8(void)
{
    Ov002Vec3 v;
    int *ctx;
    int nTint;
    int nValue;
    int i;
    int aSlide[10] = { 0 };
    Ov002Tween *pFade;
    int nDepth;
    int aFade[10] = { 0 };
    int j;
    int aDirty[10] = { 0 };
    Ov002Tween *pSlide;

    ctx = *(int **)&data_ov002_0207f628;

    if (((Ov002Tween *)((char *)ctx + 0xaf0))->bHeld != 0) {
        nTint = 0x5ec;
    } else {
        func_0203602c((char *)ctx + 0xaf0, &nTint);
    }
    if (((Ov002Tween *)((char *)ctx + 0xb0c))->bHeld != 0) {
        nDepth = 0x1f000;
    } else {
        func_0203602c((char *)ctx + 0xb0c, &nDepth);
    }

    nValue = nTint;
    *(int *)((char *)ctx + 0x97c) = nValue;
    *(int *)((char *)ctx + 0x980) = nValue;
    *(int *)((char *)ctx + 0x984) = nValue;
    func_02016d10(*(int *)((char *)ctx + 0x944), nDepth >> 12);

    pSlide = (Ov002Tween *)((char *)ctx + 0xb28);
    pFade = (Ov002Tween *)((char *)ctx + 0xc40);
    for (i = 0; i < 10; i++) {
        if (pSlide[i].bHeld != 0) {
            aSlide[i] = 0;
        } else {
            func_0203602c(&pSlide[i], &aSlide[i]);
            aDirty[i] = 1;
        }
        if (pFade[i].bHeld == 0) {
            func_0203602c(&pFade[i], &aFade[i]);
            aDirty[i] = 1;
        } else {
            if (ctx[i + 0x29] != 0) {
                ctx[i + 0x29] = 0;
            }
            aFade[i] = 0;
        }
    }

    for (i = 0; i < 10; i++) {
        if (aDirty[i] != 0) {
            for (j = 0;
                 j < func_ov002_020618d8(ctx[i + 0x364]) + 1;
                 j++) {
                func_0202afdc((char *)ctx + 0x9d4,
                              ((u16 *)ctx)[i + 0x56e]);
                if (j >= func_ov002_020618d8(ctx[i + 0x364])) {
                    func_ov002_020617f8((char *)ctx + 0x9d4, 10);
                } else {
                    func_ov002_020617f8(
                        (char *)ctx + 0x9d4,
                        func_ov002_02061908(j, ctx[i + 0x364]));
                }
                func_02016cd0(*(int *)((char *)ctx + 0xa4c), 0x3e);
                func_02016d10(*(int *)((char *)ctx + 0xa4c), aFade[i] >> 12);
                v.x = (func_ov002_020618d8(ctx[i + 0x364])
                       - j) * 0x44c - 0x1f40;
                v.y = (aSlide[i] >> 12) + 0x2d50;
                v.z = 0;
                *(Ov002Vec3 *)((char *)ctx + 0xa78) = v;
                func_ov002_0205f810((char *)ctx + 0x9d4);
            }
        }
    }
}
