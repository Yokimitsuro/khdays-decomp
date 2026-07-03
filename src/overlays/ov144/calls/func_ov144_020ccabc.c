extern int func_0203c5c0(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov144_020ccda0(void);

void func_ov144_020ccabc(char *obj) {
    void *entry = 0;
    func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 0x54, func_ov144_020ccda0, 0, &entry);
    *(char **)entry = obj;
    *(void **)(obj + 0x214) = entry;
}
