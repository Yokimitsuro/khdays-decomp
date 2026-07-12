extern void func_0203c5c0();
extern void func_ov256_020cd39c(void);
void func_ov256_020ccce8(int param_1) {
    int *entry;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 100, 0xb4, func_ov256_020cd39c, 0, &entry);
    *entry = param_1;
    entry[1] = *(int *)(*entry + 0x384);
    entry[2] = *(int *)(*entry + 0x3ac);
    *(int **)(param_1 + 0x214) = entry;
}
