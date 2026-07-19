extern void func_ov009_02052778(char *p);
extern void func_0202ffbc(char *p);
extern int func_ov009_0204e42c(void);
extern int func_ov009_0204e440(void);
extern void func_ov009_020526b8(int a);
extern void func_ov009_02051880(int a);
extern void func_ov009_020518b4(int a);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int value, void *dst, unsigned size);
extern void G3X_SetHOffset(int off);
extern void func_02020a78(int a, int b);

/* Scene teardown: releases the sub-allocators, unwinds the active object, blanks the three
 * tiled BG screens and resets the 3D horizontal offset. */
void func_ov009_02053e24(char *self) {
    int a;
    int b;
    func_ov009_02052778(self + 0x15c);
    func_0202ffbc(self + 0x1a4);
    func_0202ffbc(self + 0x168);
    func_0202ffbc(self + 0x1e0);
    a = func_ov009_0204e42c();
    b = func_ov009_0204e440();
    func_ov009_020526b8(a);
    func_ov009_02051880(b);
    func_ov009_020518b4(b);
    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
    G3X_SetHOffset(0);
    func_02020a78(1, 0);
}
