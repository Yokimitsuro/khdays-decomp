extern int func_0203c5c0(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov143_020d4160(void);

void func_ov143_020d3f50(char *obj) {
    void *entry = 0;
    func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0x4c, func_ov143_020d4160, 0, &entry);
    *(char **)entry = obj;
    *(void **)(obj + 0x214) = entry;
}
