extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov203_020d6638(void);
extern void func_ov203_020d66b8(void);

void func_ov203_020d65a8(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0xc, func_ov203_020d6638, (int)func_ov203_020d66b8, &entry);
    *(char **)entry = obj;
}
