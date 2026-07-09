extern void MI_CpuFill8();
extern int func_020342e8();
extern int func_020343cc();

void func_ov025_020b3570(unsigned int *arg0, unsigned int *arg1) {
    unsigned int v;
    MI_CpuFill8(arg0, 0, 0xc);
    v = arg1[0];
    if (v == 0) v = (unsigned int)func_020342e8;
    arg0[1] = v;
    v = arg1[1];
    if (v == 0) v = (unsigned int)func_020343cc;
    arg0[2] = v;
}
