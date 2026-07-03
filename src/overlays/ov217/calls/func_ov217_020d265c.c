extern void func_0203c5c0(int a, int b, int c, void *cb, int e5, int **out);
extern void func_ov217_020d2770(void);

int *func_ov217_020d265c(int param_1, int param_2, int param_3, int param_4) {
    int *e;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 8, func_ov217_020d2770, 0, &e);
    *e = *(int *)(param_1 + 0x3c4);
    return e;
}
