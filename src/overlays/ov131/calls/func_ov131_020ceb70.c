extern int func_0203c5c0(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov131_020cec10(void);
extern void func_ov131_020cecbc(void);

void func_ov131_020ceb70(char *obj) {
    void *entry = 0;
    func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0x10, func_ov131_020cec10, (int)func_ov131_020cecbc, &entry);
    *(char **)entry = obj;
}
