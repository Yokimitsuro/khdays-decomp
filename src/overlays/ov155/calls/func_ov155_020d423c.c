extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov155_020d4288(void);

void func_ov155_020d423c(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0x28, func_ov155_020d4288, 0, &entry);
    *(char **)entry = obj;
    *(void **)(obj + 0x214) = entry;
}
