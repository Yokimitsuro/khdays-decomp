/* Ov025_DrawListWindow -- Ov008_DrawListWindow (272 B, 9 relocs).
 * Redraws the visible rows of the scrolling menu list. Runs the layer object at self+0x190, clears
 * the two grid regions (rows 0..2 and 15..18 of block 0x1a, stride 0x20), then walks the entry list
 * at self+0x1cc. For every populated entry (node[8] != 0) that falls inside the scroll window
 * [center-1, center+0xf) it draws the entry at grid row (index % 16) via Ov025_DrawListEntryRow, and
 * tallies the entries and the kind 1/5 entries. When param_4 is set it reports the kind 1/5 count
 * (Ov025_DrawPageBElement id 5); when param_3 is set it finalizes (Ov025_PageB_UploadSurfaceDC) and marks
 * self+0x4 = 1. Returns the number of populated entries seen. Called by the scroll driver
 * Ov008_ScrollMenuMoveTo.
 * Obj_InvokeInnerVtable4 takes only the object pointer here (the trailing params Ghidra shows are the
 * caller's r1-r3 left in place); c36c/eb64's trailing args are likewise the %16 sign byproduct. */
extern void Obj_InvokeInnerVtable4(int obj);
extern void Ov025_ClearGridRows(int a, int b, int c, int d, int e);
extern int  NNS_FndGetNextListObject(void *list, int obj);
extern void Ov025_DrawListEntryRow(int self, int col, int *node);
extern int Ov025_DrawPageBElement(int param_1, int param_2, ...);
extern void Ov025_PageB_UploadSurfaceDC(void);
extern void Ov025_MarkSlotUsed(int a);

int Ov025_DrawListWindow(int self, int center, int param_3, int param_4)
{
    int iVar4 = 0, uVar5 = 0;
    int *piVar2;

    Obj_InvokeInnerVtable4(self + 0x190);
    Ov025_ClearGridRows(0x1a, 0, 0, 3, 0x20);
    Ov025_ClearGridRows(0x1a, 0xf, 0, 4, 0x20);
    for (piVar2 = (int *)NNS_FndGetNextListObject((void *)(self + 0x1cc), 0); piVar2 != 0;
         piVar2 = (int *)NNS_FndGetNextListObject((void *)(self + 0x1cc), (int)piVar2)) {
        if (piVar2[8] != 0) {
            if (center - 1 <= iVar4 && iVar4 < center + 0xf)
                Ov025_DrawListEntryRow(self, iVar4 % 16, piVar2);
            iVar4++;
            if (piVar2[2] == 5 || piVar2[2] == 1)
                uVar5++;
        }
    }
    if (param_4 != 0)
        Ov025_DrawPageBElement(5, 0, uVar5);
    if (param_3 != 0) {
        Ov025_PageB_UploadSurfaceDC();
        *(int *)(self + 4) = 1;
    }
    Ov025_MarkSlotUsed(0x1a);
    return iVar4;
}
