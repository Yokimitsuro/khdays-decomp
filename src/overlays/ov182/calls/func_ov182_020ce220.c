extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov182_020ce7ac(void);

void func_ov182_020ce220(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0x88, func_ov182_020ce7ac, 0, &entry);
    *(char **)entry = obj;
    *(void **)(obj + 0x214) = entry;
}
