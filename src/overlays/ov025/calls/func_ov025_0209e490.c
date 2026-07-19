extern char *func_ov025_02084afc(void);
extern void func_ov025_02089884(char *p);
extern void func_0202ffbc(char *p);
extern void func_ov025_020895b8(int a);
extern void func_ov025_020883a0(int a);
extern void func_ov025_020883d4(int a);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int value, void *dst, unsigned size);
extern void G3X_SetHOffset(int off);
extern char *func_ov025_02084fa8(void);

/* List screen teardown: releases the two row allocators and the layout, unwinds the two cached
 * objects, blanks the three tiled BG screens and clears the pending entry. */
void func_ov025_0209e490(void) {
    char *self = func_ov025_02084afc();
    func_ov025_02089884(self + 0x78);
    func_ov025_02089884(self + 0x6c);
    func_0202ffbc(self + 0x84);
    func_ov025_020895b8(*(int *)(self + 0xc4));
    func_ov025_020883a0(*(int *)(self + 0xc8));
    func_ov025_020883d4(*(int *)(self + 0xc8));
    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
    G3X_SetHOffset(0);
    *(int *)(func_ov025_02084fa8() + 0xc) = 0;
}
