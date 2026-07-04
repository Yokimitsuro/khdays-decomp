extern int func_02031c30(int a, int b);
extern int func_02011840(void *a, int b);
extern void func_02012480(int a, int b);

void func_02032634(int param_1, int param_2, unsigned param_3) {
    int r;
    if (param_2 < 0) return;
    r = func_02031c30(param_1, *(int *)(param_1 + param_2 * 0x8c + 0x78));
    r = func_02011840(*(unsigned short **)(r + 0x10), param_3 & 0xffff);
    func_02012480(param_1 + 0x18 + param_2 * 0x8c, r);
}
