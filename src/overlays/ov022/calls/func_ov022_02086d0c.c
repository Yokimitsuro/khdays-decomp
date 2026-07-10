extern void func_02035fb0(unsigned int *arg0, int arg1, int arg2, int arg3, int arg4);
extern void func_02035ffc(int arg0);
extern int data_ov022_020b2e74;

void func_ov022_02086d0c(int arg0) {
    int p = *(int *)&data_ov022_020b2e74;
    if (arg0 != 0) {
        func_02035fb0((unsigned int *)(p + 0x1e0), 1, 0, 0x10000, 400);
        func_02035ffc(p + 0x1e0);
        return;
    }
    func_02035fb0((unsigned int *)(p + 0x1e0), 2, 0x10000, 0, 400);
    func_02035ffc(p + 0x1e0);
}
