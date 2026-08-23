/*
 * Ov002_SceneDestroy - tear the panel scene down and let go of its block.
 *
 * The surfaces are closed first, then every string the scene owns is freed: the
 * picture, the caption, and the three entry lines. The record set and its
 * drawing context are only torn down when the scene actually built them. The
 * object itself is destroyed last, and the pointer the whole overlay reaches the
 * scene through is cleared.
 *
 * THUMB.
 */

extern int data_ov002_0207f624;

extern void NNSi_FndFreeFromDefaultHeap(int pBlock);
extern void func_0202ffbc(void *pContext);
extern void func_02024fd4(int nObject);

extern void func_ov002_0205eb78(void);
extern void func_ov002_02052834(void *pSet);

void func_ov002_0205ee80(void)
{
    int i;
    int *ctx;
    int *pWalk;

    ctx = *(int **)&data_ov002_0207f624;
    func_ov002_0205eb78();

    if (*(int *)((char *)ctx + 0x68c) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)((char *)ctx + 0x68c));
    }
    if (*(int *)((char *)ctx + 0x7c0) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)((char *)ctx + 0x7c0));
    }

    i = 0;
    pWalk = ctx;
    do {
        if (*(int *)((char *)pWalk + 0x7c4) != 0) {
            NNSi_FndFreeFromDefaultHeap(*(int *)((char *)pWalk + 0x7c4));
        }
        i++;
        pWalk = (int *)((char *)pWalk + 4);
    } while (i < 3);

    if (ctx[1] != 0) {
        NNSi_FndFreeFromDefaultHeap(ctx[1]);
    }

    if (*(int *)((char *)ctx + 0x664) != 0) {
        func_ov002_02052834((char *)ctx + 0x7ac);
        func_0202ffbc((char *)ctx + 0x770);
    }

    func_02024fd4(*(int *)((char *)ctx + 0x7e4));
    *(int **)&data_ov002_0207f624 = 0;
}
