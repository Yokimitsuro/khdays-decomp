extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov147_020ce14c(void);

void func_ov147_020ce100(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0x34, func_ov147_020ce14c, 0, &entry);
    *(char **)entry = obj;
    *(void **)(obj + 0x214) = entry;
}
