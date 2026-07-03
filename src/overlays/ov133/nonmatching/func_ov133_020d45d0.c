extern int func_0203c5c0(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov133_020d4670(void);
extern void func_ov133_020d471c(void);

void func_ov133_020d45d0(char *obj) {
    void *entry = 0;
    func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0x10, func_ov133_020d4670, (int)func_ov133_020d471c, &entry);
    *(char **)entry = obj;
}
