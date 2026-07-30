/* func_ov008_0206c690 -- Ov008_DrawListWindow (272 B, 9 relocs).
 * Redraws the visible rows of the scrolling menu list. Runs the layer object at self+0x190, clears
 * the two grid regions (rows 0..2 and 15..18 of block 0x1a, stride 0x20), then walks the entry list
 * at self+0x1cc. For every populated entry (node[8] != 0) that falls inside the scroll window
 * [center-1, center+0xf) it draws the entry at grid row (index % 16) via func_ov008_0206c36c, and
 * tallies the entries and the kind 1/5 entries. When param_4 is set it reports the kind 1/5 count
 * (func_ov008_0206eb64 id 5); when param_3 is set it finalizes (func_ov008_0206f35c) and marks
 * self+0x4 = 1. Returns the number of populated entries seen. Called by the scroll driver
 * func_ov008_0206c90c.
 * func_02030158 takes only the object pointer here (the trailing params Ghidra shows are the
 * caller's r1-r3 left in place); c36c/eb64's trailing args are likewise the %16 sign byproduct. */
extern void func_02030158(int obj);
extern void func_ov008_02050bb0(int a, int b, int c, int d, int e);
extern int  NNS_FndGetNextListObject(void *list, int obj);
extern void func_ov008_0206c36c(int self, int col, int *node);
extern int  func_ov008_0206eb64(int id, int a, ...);
extern void func_ov008_0206f35c(void);
extern void func_ov008_02050b3c(int a);

int func_ov008_0206c690(int self, int center, int param_3, int param_4)
{
    int iVar4 = 0, uVar5 = 0;
    int *piVar2;

    func_02030158(self + 0x190);
    func_ov008_02050bb0(0x1a, 0, 0, 3, 0x20);
    func_ov008_02050bb0(0x1a, 0xf, 0, 4, 0x20);
    for (piVar2 = (int *)NNS_FndGetNextListObject((void *)(self + 0x1cc), 0); piVar2 != 0;
         piVar2 = (int *)NNS_FndGetNextListObject((void *)(self + 0x1cc), (int)piVar2)) {
        if (piVar2[8] != 0) {
            if (center - 1 <= iVar4 && iVar4 < center + 0xf)
                func_ov008_0206c36c(self, iVar4 % 16, piVar2);
            iVar4++;
            if (piVar2[2] == 5 || piVar2[2] == 1)
                uVar5++;
        }
    }
    if (param_4 != 0)
        func_ov008_0206eb64(5, 0, uVar5);
    if (param_3 != 0) {
        func_ov008_0206f35c();
        *(int *)(self + 4) = 1;
    }
    func_ov008_02050b3c(0x1a);
    return iVar4;
}
