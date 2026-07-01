extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov202_020cebdc(void);
extern void func_ov202_020cec88(void);

void func_ov202_020ceb3c(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0x10, func_ov202_020cebdc, (int)func_ov202_020cec88, &entry);
    *(char **)entry = obj;
}
