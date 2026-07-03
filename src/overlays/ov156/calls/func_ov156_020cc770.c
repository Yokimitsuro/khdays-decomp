extern int func_0203c5c0(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov156_020ccd54(void);

void func_ov156_020cc770(char *obj) {
    void *entry = 0;
    func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0x3c, func_ov156_020ccd54, 0, &entry);
    *(char **)entry = obj;
    *(void **)(obj + 0x214) = entry;
}
