extern int func_0203c5c0(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov161_020cc694(void);
extern void func_ov161_020cc740(void);

void func_ov161_020cc5f4(char *obj) {
    void *entry = 0;
    func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0x10, func_ov161_020cc694, (int)func_ov161_020cc740, &entry);
    *(char **)entry = obj;
}
