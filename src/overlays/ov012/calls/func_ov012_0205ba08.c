extern int func_02021948(void *a);
extern void func_ov012_0205bb84(int x);
extern void func_ov012_0205c224(int x, int y);
extern void func_ov012_0205c278(int x);

int func_ov012_0205ba08(char *arg1) {
    int v = func_02021948(arg1);
    func_ov012_0205bb84(*(int *)(*(int *)(arg1 + 0x128) + 0xc));
    func_ov012_0205c224(*(int *)(*(int *)(arg1 + 0x128) + 0xc), v);
    func_ov012_0205c278(*(int *)(*(int *)(arg1 + 0x128) + 0xc));
    return 1;
}
