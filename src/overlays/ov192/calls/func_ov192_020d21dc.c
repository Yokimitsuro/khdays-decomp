extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov192_020d27fc(void);

void func_ov192_020d21dc(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0x3c, func_ov192_020d27fc, 0, &entry);
    *(char **)entry = obj;
    *(void **)(obj + 0x214) = entry;
}
