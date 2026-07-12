extern void func_0203c5c0();
extern void func_ov246_020d07b0(void);
void func_ov246_020d0360(int param_1) {
    int *entry;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 100, 0x58, func_ov246_020d07b0, 0, &entry);
    *entry = param_1;
    entry[1] = *(int *)(*entry + 0x388);
    *(int **)(param_1 + 0x214) = entry;
}
