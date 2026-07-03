extern int func_0203c5c0(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov164_020d2b08(void);
extern void func_ov164_020d2b88(void);

void func_ov164_020d2a78(char *obj) {
    void *entry = 0;
    func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0xc, func_ov164_020d2b08, (int)func_ov164_020d2b88, &entry);
    *(char **)entry = obj;
}
