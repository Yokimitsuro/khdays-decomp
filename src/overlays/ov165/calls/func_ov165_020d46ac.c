extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov165_020d474c(void);
extern void func_ov165_020d47f8(void);

void func_ov165_020d46ac(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0x10, func_ov165_020d474c, (int)func_ov165_020d47f8, &entry);
    *(char **)entry = obj;
}
