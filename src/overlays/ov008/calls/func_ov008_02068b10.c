extern void func_ov008_02055c74(char *p);
extern void func_0202ffbc(char *p);
extern int func_ov008_02050c28(void);
extern int func_ov008_02050c54(void);
extern void func_ov008_020559a8(int a);
extern void func_ov008_020546ec(int a);
extern void func_ov008_02054720(int a);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int value, void *dst, unsigned size);
extern void G3X_SetHOffset(int off);

/* Scene teardown: releases the sub-allocators, unwinds the active object, blanks the three
 * tiled BG screens and resets the 3D horizontal offset. */
void func_ov008_02068b10(char *self) {
    int a;
    int b;
    func_ov008_02055c74(self + 0x158);
    func_0202ffbc(self + 0x1a0);
    func_0202ffbc(self + 0x164);
    func_0202ffbc(self + 0x1dc);
    a = func_ov008_02050c28();
    b = func_ov008_02050c54();
    func_ov008_020559a8(a);
    func_ov008_020546ec(b);
    func_ov008_02054720(b);
    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
    G3X_SetHOffset(0);
}
