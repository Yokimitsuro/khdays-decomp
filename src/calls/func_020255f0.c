extern int func_020255d4(int a, int b, int c);
extern int func_02017088(int entry);
extern void func_02023768(int a, int b, int c, int d);

void func_020255f0(int param_1, int param_2, int param_3) {
    int entry = func_020255d4(param_1, 7, 0);
    int base;
    if (entry == 0) return;
    base = func_02017088(entry);
    if (base == 0) return;
    func_02023768(param_2, param_1, base + *(int *)(base + 0x14) - param_1, param_3);
}
