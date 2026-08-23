/*
 * Ov002_SceneReopenPanel - bring the panel back up after the caller changed
 * what it should show.
 *
 * Nothing happens if the scene is gone. A request pointer, when one is given,
 * is applied first. The window is then reopened at 0x20 wide, the caption box
 * takes a fresh tile buffer and is uploaded, and the entry box does the same
 * when there is anything in it. The pen is put back to the top left.
 *
 * Where it goes from there depends on whether the caller asked for a picture:
 * without one the scene loads the tile set for the picture slot and moves to
 * state 1; with one the surface is built (once) and the scene moves to state 2.
 * Either way the step that follows is armed and the entry either side of the
 * panel is selected.
 *
 * THUMB.
 */

extern int data_ov002_0207f624;
extern int data_ov002_0207eb28[];

extern void func_0202ff8c(void *pSurface, const void *pConfig);
extern void func_020300f8(void *pSurface);
extern void func_02023a44(int nObject, void *pStep);

extern void func_ov002_02052368(void *pSurface, int nKind, int nSize, int a0,
                                int a1, int a2, int a3, int nBufferA,
                                int nBufferB, void *pSource, int nLast);
extern void func_ov002_02052a6c(int nFile, void *pStep, int nValue);
extern void func_ov002_020539f4(int nKey);
extern void func_ov002_02053b28(int a, int b, int c, int d, int e);
extern int func_ov002_02053bb8(int nId);
extern void func_ov002_02053cd4(int nId);
extern void func_ov002_0205e4f0(void *pNode);
extern int func_ov002_0205ef10(void);
extern int func_ov002_0205ef18(void);
extern void func_ov002_0205f220(void *pRequest, int *pScene);

void func_ov002_0205f240(void *pRequest)
{
    void *pSource;
    int *p;
    int nBufferA;
    int *ctx;
    int nBufferB;

    ctx = *(int **)&data_ov002_0207f624;
    if (ctx == 0) {
        return;
    }

    if (pRequest != 0) {
        func_ov002_0205f220(pRequest, &data_ov002_0207f624);
    }
    func_ov002_020539f4(*(int *)((char *)ctx + 0x69c));
    func_ov002_02053b28(9, 0, 0, 0x20, 0x20);

    *(int *)((char *)ctx + 0x6c0) = func_ov002_02053bb8(9);
    func_0202ff8c((char *)ctx + 0x6f8, (char *)ctx + 0x6a8);
    func_020300f8((char *)ctx + 0x6f8);
    *(int *)((char *)ctx + 0x7b8) = 1;

    if (*(int *)((char *)ctx + 0x7e0) > 0) {
        *(int *)((char *)ctx + 0x6e8) = func_ov002_02053bb8(9);
        func_0202ff8c((char *)ctx + 0x734, (char *)ctx + 0x6d0);
        func_020300f8((char *)ctx + 0x734);
        *(int *)((char *)ctx + 0x7bc) = 1;
    }

    func_ov002_02053cd4(9);
    pSource = 0;
    *(int *)((char *)ctx + 0x7d0) = 0;
    *(int *)((char *)ctx + 0x7d4) = 0;
    *(int *)((char *)ctx + 0x7d8) = 0;

    if (*(int *)((char *)ctx + 0x664) != 0) {
        p = (int *)((char *)ctx + 0x668);
        if (*(int *)((char *)ctx + 0x660) == 0) {
            if (p[9] != 0) {
                pSource = p + 10;
            }
            nBufferA = func_ov002_02053bb8(0xb);
            nBufferB = func_ov002_02053bb8(10);
            func_ov002_02052368((char *)ctx + 0xc, 3, 0, p[0], p[1], p[2], p[3],
                                nBufferA, nBufferB, pSource, 0xe);
            *(int *)((char *)ctx + 0x660) = 1;
        }
        ctx[0] = 2;
        func_02023a44(*(int *)((char *)ctx + 0x6a4), func_ov002_0205ef18);
    } else {
        func_ov002_02052a6c(data_ov002_0207eb28[*(int *)((char *)ctx + 0x67c)],
                            func_ov002_0205e4f0, 0);
        ctx[0] = 1;
        func_02023a44(*(int *)((char *)ctx + 0x6a4), func_ov002_0205ef10);
    }

    func_ov002_020539f4(*(int *)((char *)ctx + 0x6a0));
}
