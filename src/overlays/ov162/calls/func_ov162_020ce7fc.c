extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov162_020ce844(void);
extern void func_ov162_020ce8c0(void);

void func_ov162_020ce7fc(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0xc, func_ov162_020ce844, (int)func_ov162_020ce8c0, &entry);
    *(char **)entry = obj;
}
