extern void func_ov238_020d0f54(int self, int param_2, int param_3, int param_4, void *cb);
extern void func_ov238_020d1290(void);

void func_ov238_020d1258(int param_1) {
    int obj = *(int *)(param_1 + 4);
    *(int *)(obj + 0x20) = 0;
    *(signed char *)(obj + 0x31) = 2;
    *(signed char *)(obj + 0x2d) = 2;
    func_ov238_020d0f54(param_1, 0x12, 8, 0, (void *)&func_ov238_020d1290);
}
