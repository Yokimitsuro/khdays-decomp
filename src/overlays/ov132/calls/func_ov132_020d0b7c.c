extern int func_0203c5c0(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov132_020d0c0c(void);
extern void func_ov132_020d0c8c(void);

void func_ov132_020d0b7c(char *obj) {
    void *entry = 0;
    func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0xc, func_ov132_020d0c0c, (int)func_ov132_020d0c8c, &entry);
    *(char **)entry = obj;
}
