extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov163_020d0b0c(void);
extern void func_ov163_020d0bb8(void);

void func_ov163_020d0a6c(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0x10, func_ov163_020d0b0c, (int)func_ov163_020d0bb8, &entry);
    *(char **)entry = obj;
}
