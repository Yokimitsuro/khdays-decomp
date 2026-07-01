extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov299_020d3a30(void);

void func_ov299_020d39e4(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0xc, func_ov299_020d3a30, 0, &entry);
    *(char **)entry = obj;
    *(void **)(obj + 0x214) = entry;
}
