extern int func_0203c5c0(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov164_020d292c(void);
extern void func_ov164_020d29d8(void);

void func_ov164_020d288c(char *obj) {
    void *entry = 0;
    func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0x10, func_ov164_020d292c, (int)func_ov164_020d29d8, &entry);
    *(char **)entry = obj;
}
