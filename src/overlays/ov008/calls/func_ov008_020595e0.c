extern void func_ov008_0205a628(char *p);
extern void func_ov008_02058a04(char *self);
extern void func_ov008_02055c74(char *p);
extern void func_0202ffbc(char *p);
extern int func_ov008_02050c28(void);
extern int func_ov008_02050c54(void);
extern void func_ov008_020559a8(int a);
extern void func_ov008_020546ec(int a);
extern void func_ov008_02054720(int a);
extern void func_ov008_0205477c(int a, int b);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int value, void *dst, unsigned size);
extern void G3X_SetHOffset(int off);

/* Scene teardown: releases the sub-allocators, unwinds the active object, blanks the three
 * tiled BG screens and resets the 3D horizontal offset. */
void func_ov008_020595e0(char *self) {
    int a;
    int b;
    func_ov008_0205a628(self + 0x98);
    func_ov008_02058a04(self);
    func_ov008_02055c74(self + 4);
    func_0202ffbc(self + 0x4c);
    func_0202ffbc(self + 0x10);
    a = func_ov008_02050c28();
    b = func_ov008_02050c54();
    func_ov008_020559a8(a);
    func_ov008_020546ec(b);
    func_ov008_02054720(b);
    func_ov008_0205477c(b, 0);
    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
    G3X_SetHOffset(0);
}
