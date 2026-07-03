extern int func_0203c5c0(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov175_020ce4d8(void);

void func_ov175_020ce48c(char *obj) {
    void *entry = 0;
    func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0x24, func_ov175_020ce4d8, 0, &entry);
    *(char **)entry = obj;
    *(void **)(obj + 0x214) = entry;
}
