extern void func_0203c5c0();
extern void func_ov254_020d2414(void);
void func_ov254_020d23b8(int param_1) {
    int *entry;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 100, 0x24, func_ov254_020d2414, 0, &entry);
    *entry = param_1;
    entry[1] = *(int *)(*entry + 0x384);
    *(int **)(param_1 + 0x214) = entry;
}
