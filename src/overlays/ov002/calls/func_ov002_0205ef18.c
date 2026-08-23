/*
 * Ov002_SceneOpenPanelStep - the step that waits for the fade and then puts the
 * panel on screen.
 *
 * Nothing happens while a fade of kind 2 is still running. Once it is clear the
 * two entries either side of the panel are selected, the surface is brought up
 * and the two scratch buffers are released. Only when the surface reports state
 * 3 is the scene moved on: the window is opened at 0x20 wide and the scene hands
 * back the step that runs from there.
 *
 * ARM.
 */

extern int data_ov002_0207f624;

extern int func_02023c40(void);
extern int func_02023c50(void);

extern void func_ov002_020526b0(void *pSurface);
extern void func_ov002_020539f4(int nKey);
extern void func_ov002_02053b28(int a, int b, int c, int d, int e);
extern void func_ov002_02053cd4(int nId);
extern int func_ov002_0205efb4(void);

void *func_ov002_0205ef18(void)
{
    int *ctx;
    void *pNext;

    pNext = 0;
    ctx = *(int **)&data_ov002_0207f624;
    if (func_02023c40() == 2 && (func_02023c50() & 1) == 1) {
        return 0;
    }

    func_ov002_020539f4(*(int *)((char *)ctx + 0x69c));
    func_ov002_020526b0((char *)ctx + 0xc);
    func_ov002_02053cd4(0xa);
    func_ov002_02053cd4(0xb);

    if (ctx[3] == 3) {
        func_ov002_02053b28(9, 0, 0, 0x20, 4);
        ctx[0] = 3;
        pNext = func_ov002_0205efb4;
    }

    func_ov002_020539f4(*(int *)((char *)ctx + 0x6a0));
    return pNext;
}
