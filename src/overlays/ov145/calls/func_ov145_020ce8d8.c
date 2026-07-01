extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov145_020cebbc(void);

void func_ov145_020ce8d8(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0x54, func_ov145_020cebbc, 0, &entry);
    *(char **)entry = obj;
    *(void **)(obj + 0x214) = entry;
}
