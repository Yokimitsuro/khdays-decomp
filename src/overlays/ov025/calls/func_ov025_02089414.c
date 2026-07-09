extern int func_ov025_02088d2c();
extern void MI_CpuFill8();
extern void func_02011a6c();

unsigned int * func_ov025_02089414(int arg0, unsigned int arg1, unsigned short arg2) {
    unsigned int *p = (unsigned int *)func_ov025_02088d2c(arg0);
    MI_CpuFill8(p, 0, 0x10);
    *(unsigned short *)p = arg2;
    p[1] = arg1;
    func_02011a6c(arg1, p + 2);
    p[3] = 1;
    return p;
}
