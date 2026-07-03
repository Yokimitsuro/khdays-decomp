extern int func_0203c5c0(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov161_020cc870(void);
extern void func_ov161_020cc8f0(void);

void func_ov161_020cc7e0(char *obj) {
    void *entry = 0;
    func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0xc, func_ov161_020cc870, (int)func_ov161_020cc8f0, &entry);
    *(char **)entry = obj;
}
