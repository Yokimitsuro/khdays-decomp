extern int func_ov025_02084afc();
extern void MI_CpuFill8();

void func_ov025_0209c334(int arg0) {
    int x = func_ov025_02084afc(arg0);
    MI_CpuFill8(x, 0, 0xbc);
    *(int *)(x + 0xb4) = 0;
    *(int *)(x + 0xb8) = 0;
    *(short *)(x + 2) = 0;
}
