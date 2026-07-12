extern void func_0203c5c0();
extern void func_ov245_020d2eb4(void);
void func_ov245_020d2e58(int param_1) {
    int *entry;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 100, 0x50, func_ov245_020d2eb4, 0, &entry);
    *entry = param_1;
    entry[1] = *(int *)(*entry + 0x9c);
    *(int **)(param_1 + 0x214) = entry;
}
