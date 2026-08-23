/*
 * Ov002_ScenePanelIdleStep - the panel's per-frame step once it is open.
 *
 * The entry lines are redrawn and the caption box flushed every frame. B closes
 * the panel outright. A on a panel that has entries opens the entry it is on.
 * Anything that dismisses an empty panel - A, B or start - closes the window
 * instead, plays the sound that goes with what was on screen, and lets the
 * closing step take over.
 *
 * ARM.
 */

typedef unsigned short u16;

extern int data_ov002_0207f624;
extern u16 data_0204c190;

extern void func_020300f8(void *pSurface);
extern void func_02033b78(int nId, int nKind);

extern void func_ov002_020539f4(int nKey);
extern void func_ov002_02053b28(int a, int b, int c, int d, int e);
extern void func_ov002_0205eaf0(void);
extern void func_ov002_0205ed58(void);
extern void func_ov002_0205ed98(void);
extern void func_ov002_0205f50c(void);

void *func_ov002_0205f084(void)
{
    int *ctx;
    int nButtons;
    int nCount;

    ctx = *(int **)&data_ov002_0207f624;
    func_ov002_020539f4(*(int *)((char *)ctx + 0x69c));
    func_ov002_0205eaf0();
    func_020300f8((char *)ctx + 0x6f8);

    nButtons = data_0204c190;
    if (nButtons & 0x40) {
        func_ov002_0205ed98();
    } else {
        nCount = *(int *)((char *)ctx + 0x7e0);
        if (nCount > 0 && (nButtons & 0x80)) {
            func_ov002_0205ed58();
        } else if ((nButtons & 1) || (nCount == 0 && (nButtons & 0x82))) {
            func_ov002_02053b28(9, 0, 0, 0x20, 0x18);
            func_ov002_0205f50c();
            func_02033b78(0, *(int *)((char *)ctx + 0x7e0) > 0 ? 1 : 0xa);
        }
    }

    func_ov002_020539f4(*(int *)((char *)ctx + 0x6a0));
    return 0;
}
