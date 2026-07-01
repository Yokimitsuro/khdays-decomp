extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov243_020d3f70(void);

void func_ov243_020d3c48(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0x44, func_ov243_020d3f70, 0, &entry);
    *(char **)entry = obj;
    *(void **)(obj + 0x214) = entry;
}
