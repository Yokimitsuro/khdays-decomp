extern void func_ov025_0208cb6c(char *p);
extern void func_ov025_02089884(char *self);
extern void func_0202ffbc(char *p);
extern int func_ov025_02084a50(void);
extern int func_ov025_02084a7c(void);
extern void func_ov025_020895b8(int a);
extern void func_ov025_020883a0(int a);
extern void func_ov025_020883d4(int a);
extern void func_ov025_02088430(int a, int b);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int value, void *dst, unsigned size);
extern void G3X_SetHOffset(int off);

/* Scene teardown: releases the sub-allocators, unwinds the active object, blanks the three
 * tiled BG screens and resets the 3D horizontal offset. */
void func_ov025_0208beb4(char *self) {
    int a;
    int b;
    func_ov025_0208cb6c(self + 0x98);
    func_ov025_02089884(self + 4);
    func_0202ffbc(self + 0x4c);
    func_0202ffbc(self + 0x10);
    a = func_ov025_02084a50();
    b = func_ov025_02084a7c();
    func_ov025_020895b8(a);
    func_ov025_020883a0(b);
    func_ov025_020883d4(b);
    func_ov025_02088430(b, 0);
    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
    G3X_SetHOffset(0);
}
