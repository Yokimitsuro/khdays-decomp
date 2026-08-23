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

typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

extern int data_ov002_0207f628;

extern void func_02035f84(void *pTween);
extern void func_ov002_02061830(void *pWidget, int nFrame);
extern void func_02016d10(int nList, int nValue);

extern void func_ov002_0205f5a8(void *pWidget, unsigned int nFileId, int nKind,
                                int nParam);

void func_ov002_0205f61c(void)
{
    int i;
    void *pTweenA;
    void *pTweenB;
    Ov002Vec3 v;
    void *pTweenC;
    int *pWalk;
    int *ctx;

    ctx = *(int **)&data_ov002_0207f628;
    func_02035f84((char *)ctx + 0x754);
    func_02035f84((char *)ctx + 0x770);
    func_02035f84((char *)ctx + 0x78c);
    func_02035f84((char *)ctx + 0x7a8);

    func_ov002_0205f5a8((char *)ctx + 0xe8,
                        0x80000001
                            | ((*(int *)((char *)ctx + 0x3c) + 0x8000) & 0xfffffc)
                                  << 7,
                        0x3b, 0xd71);
    func_ov002_02061830((char *)ctx + 0xe8, 0);

    func_ov002_0205f5a8((char *)ctx + 0x508,
                        0x80000003
                            | ((*(int *)((char *)ctx + 0x3c) + 0x8000) & 0xfffffc)
                                  << 7,
                        0x3c, 0x5ec);
    func_02016d10(*(int *)((char *)ctx + 0x580), 0x16);

    func_ov002_0205f5a8((char *)ctx + 0x1f0,
                        0x80000002
                            | ((*(int *)((char *)ctx + 0x3c) + 0x8000) & 0xfffffc)
                                  << 7,
                        0x3e, 0xccd);
    func_ov002_02061830((char *)ctx + 0x1f0, 0);

    func_ov002_0205f5a8((char *)ctx + 0x2f8,
                        (((*(int *)((char *)ctx + 0x3c) + 0x8000) & 0xfffffc)
                         << 7)
                            | 0x80000004,
                        0x39, 0x800);
    func_02016d10(*(int *)((char *)ctx + 0x370), 0);

    v.x = -0x4718;
    v.y = 0x3520;
    i = 0;
    v.z = 0;
    *(Ov002Vec3 *)((char *)ctx + 0x18c) = v;
    *(Ov002Vec3 *)((char *)ctx + 0x39c) = v;
    v.z = 0x3000;
    *(Ov002Vec3 *)((char *)ctx + 0x294) = v;

    pWalk = ctx;
    v.x = -0x3a98;
    v.y = 0x2ee0;
    v.z = 0x4000;
    *(Ov002Vec3 *)((char *)ctx + 0x5ac) = v;

    pTweenA = (char *)ctx + 0x7c8;
    pTweenB = (char *)ctx + 0x81c;
    pTweenC = (char *)ctx + 0x870;
    do {
        func_02035f84(pTweenA);
        func_02035f84(pTweenB);
        func_02035f84(pTweenC);
        *(int *)((char *)pWalk + 0x718) = 0;
        *(int *)((char *)pWalk + 0x71c) = 0;
        *(int *)((char *)pWalk + 0x720) = 0;
        pWalk = (int *)((char *)pWalk + 0xc);
        pTweenA = (char *)pTweenA + 0x1c;
        pTweenB = (char *)pTweenB + 0x1c;
        pTweenC = (char *)pTweenC + 0x1c;
        i++;
    } while (i < 3);

    func_ov002_0205f5a8((char *)ctx + 0x400,
                        0x80000005
                            | ((*(int *)((char *)ctx + 0x3c) + 0x8000) & 0xfffffc)
                                  << 7,
                        0x3a, 0x5ec);
}
