extern void func_0203c5c0();
extern void func_ov259_020d1f24(void);
void func_ov259_020d1c68(int param_1) {
    int *entry;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 100, 0x54, func_ov259_020d1f24, 0, &entry);
    *entry = param_1;
    entry[1] = *entry + 0x384;
    *(int **)(param_1 + 0x214) = entry;
}
