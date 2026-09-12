extern void func_ov238_020d0f54(int self, int param_2, int param_3, int param_4, void *cb);
extern void func_ov238_020d2020(void);

void func_ov238_020d1fe0(int param_1) {
    int obj = *(int *)(param_1 + 4);
    *(signed char *)(obj + 0x2d) = 3;
    *(signed char *)(obj + 0x2c) = 2;
    *(int *)(obj + 0x20) = 0;
    *(signed char *)(obj + 0x31) = 1;
    func_ov238_020d0f54(param_1, 5, 1, 0, (void *)&func_ov238_020d2020);
}
