extern int func_0203c5c0(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov167_020d207c(void);

void func_ov167_020d2030(char *obj) {
    void *entry = 0;
    func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0x2c, func_ov167_020d207c, 0, &entry);
    *(char **)entry = obj;
    *(void **)(obj + 0x214) = entry;
}
