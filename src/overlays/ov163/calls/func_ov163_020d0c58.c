extern int func_0203c5c0(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov163_020d0ce8(void);
extern void func_ov163_020d0d68(void);

void func_ov163_020d0c58(char *obj) {
    void *entry = 0;
    func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0xc, func_ov163_020d0ce8, (int)func_ov163_020d0d68, &entry);
    *(char **)entry = obj;
}
