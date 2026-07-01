extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov202_020cedb8(void);
extern void func_ov202_020cee38(void);

void func_ov202_020ced28(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0xc, func_ov202_020cedb8, (int)func_ov202_020cee38, &entry);
    *(char **)entry = obj;
}
