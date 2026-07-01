extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov161_020cca24(void);
extern void func_ov161_020ccaa0(void);

void func_ov161_020cc9dc(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0xc, func_ov161_020cca24, (int)func_ov161_020ccaa0, &entry);
    *(char **)entry = obj;
}
