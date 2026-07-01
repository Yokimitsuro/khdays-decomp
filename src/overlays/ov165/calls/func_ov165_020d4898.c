extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov165_020d4928(void);
extern void func_ov165_020d49a8(void);

void func_ov165_020d4898(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0xc, func_ov165_020d4928, (int)func_ov165_020d49a8, &entry);
    *(char **)entry = obj;
}
