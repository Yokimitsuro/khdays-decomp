extern int func_ov025_02084b14();
extern void MI_CpuFill8();
extern int func_ov025_020a0ef0();

void func_ov025_020afdb0(int arg0) {
    int x = func_ov025_02084b14(arg0);
    MI_CpuFill8(x, 0, 0x84);
    *(int *)(x + 0x50) = func_ov025_020a0ef0();
}
