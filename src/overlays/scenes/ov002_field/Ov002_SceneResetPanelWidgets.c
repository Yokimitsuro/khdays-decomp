/*
 * Ov002_SceneResetPanelWidgets - put every widget the panel scene owns back to
 * its opening pose.
 *
 * The four standing tweens are cleared, then each widget is pointed at its own
 * cell of the scene's archive and given its kind: the two label widgets are also
 * rewound to frame 0, and the two lists are asked to reset their elements. The
 * three fixed positions are written next - two share the same vector, the third
 * only differs in depth - and then the three moving widgets are cleared in a
 * loop along with the three words that hold their state.
 *
 * THUMB.
 */

#include "nitro/fx_types.h"
#include "game/archive.h"

extern int data_ov002_0207f628;

extern void Tween_Clear(void *pTween);
extern void Ov002_RewindWidget(void *pWidget, int nFrame);
extern void NNS_G3dMdlSetMdlAlphaAll(int nList, int nValue);

extern void Ov002_RetargetWidget(void *pWidget, unsigned int nFileId, int nKind,
                                int nParam);

void Ov002_SceneResetPanelWidgets(void)
{
    int i;
    void *pTweenA;
    void *pTweenB;
    VecFx32 v;
    void *pTweenC;
    int *pWalk;
    int *ctx;

    ctx = *(int **)&data_ov002_0207f628;
    Tween_Clear((char *)ctx + 0x754);
    Tween_Clear((char *)ctx + 0x770);
    Tween_Clear((char *)ctx + 0x78c);
    Tween_Clear((char *)ctx + 0x7a8);

    Ov002_RetargetWidget((char *)ctx + 0xe8,
                        ARCHIVE_HANDLE(*(int *)((char *)ctx + 0x3c), 1),
                        0x3b, 0xd71);
    Ov002_RewindWidget((char *)ctx + 0xe8, 0);

    Ov002_RetargetWidget((char *)ctx + 0x508,
                        ARCHIVE_HANDLE(*(int *)((char *)ctx + 0x3c), 3),
                        0x3c, 0x5ec);
    NNS_G3dMdlSetMdlAlphaAll(*(int *)((char *)ctx + 0x580), 0x16);

    Ov002_RetargetWidget((char *)ctx + 0x1f0,
                        ARCHIVE_HANDLE(*(int *)((char *)ctx + 0x3c), 2),
                        0x3e, 0xccd);
    Ov002_RewindWidget((char *)ctx + 0x1f0, 0);

    Ov002_RetargetWidget((char *)ctx + 0x2f8,
                        ARCHIVE_HANDLE(*(int *)((char *)ctx + 0x3c), 4),
                        0x39, 0x800);
    NNS_G3dMdlSetMdlAlphaAll(*(int *)((char *)ctx + 0x370), 0);

    v.x = -0x4718;
    v.y = 0x3520;
    i = 0;
    v.z = 0;
    *(VecFx32 *)((char *)ctx + 0x18c) = v;
    *(VecFx32 *)((char *)ctx + 0x39c) = v;
    v.z = 0x3000;
    *(VecFx32 *)((char *)ctx + 0x294) = v;

    pWalk = ctx;
    v.x = -0x3a98;
    v.y = 0x2ee0;
    v.z = 0x4000;
    *(VecFx32 *)((char *)ctx + 0x5ac) = v;

    pTweenA = (char *)ctx + 0x7c8;
    pTweenB = (char *)ctx + 0x81c;
    pTweenC = (char *)ctx + 0x870;
    do {
        Tween_Clear(pTweenA);
        Tween_Clear(pTweenB);
        Tween_Clear(pTweenC);
        *(int *)((char *)pWalk + 0x718) = 0;
        *(int *)((char *)pWalk + 0x71c) = 0;
        *(int *)((char *)pWalk + 0x720) = 0;
        pWalk = (int *)((char *)pWalk + 0xc);
        pTweenA = (char *)pTweenA + 0x1c;
        pTweenB = (char *)pTweenB + 0x1c;
        pTweenC = (char *)pTweenC + 0x1c;
        i++;
    } while (i < 3);

    Ov002_RetargetWidget((char *)ctx + 0x400,
                        ARCHIVE_HANDLE(*(int *)((char *)ctx + 0x3c), 5),
                        0x3a, 0x5ec);
}
