extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov151_020ce2f8(void);

void func_ov151_020ce2b0(char *obj) {
    char *p = *(char **)(obj + 0x4);
    if (*(int *)(p + 0x14) > 0x80) return;
    *(int *)(p + 0x30) = 0;
    func_ov107_020c9264(*(int *)p, 2, 1);
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov151_020ce2f8);
}
