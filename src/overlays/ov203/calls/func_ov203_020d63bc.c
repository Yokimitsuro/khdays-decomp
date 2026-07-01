extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov203_020d645c(void);
extern void func_ov203_020d6508(void);

void func_ov203_020d63bc(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0x10, func_ov203_020d645c, (int)func_ov203_020d6508, &entry);
    *(char **)entry = obj;
}
