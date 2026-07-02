extern void func_0203c5c0(int, int, int, void *, int, int **);
extern void func_ov131_020ccb94(void);

void func_ov131_020cc840(int param_1, int param_2, int param_3, int param_4) {
    int *entry;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 100, 0x60, func_ov131_020ccb94, 0, &entry);
    *entry = param_1;
    entry[1] = *(int *)(*entry + 900);
    *(int **)(param_1 + 0x214) = entry;
}
