extern int func_0203c5c0(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov131_020cedec(void);
extern void func_ov131_020cee6c(void);

void func_ov131_020ced5c(char *obj) {
    void *entry = 0;
    func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0xc, func_ov131_020cedec, (int)func_ov131_020cee6c, &entry);
    *(char **)entry = obj;
}
