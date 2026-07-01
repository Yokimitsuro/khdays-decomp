extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov140_020d1df8(void);

void func_ov140_020d1dac(char *obj) {
    char *p = *(char **)(obj + 4);
    int val = *(int *)(p + 0x3c) + *(int *)(*(char **)obj + 0x2c);
    *(int *)(p + 0x3c) = val;
    if (val < 0x4000) return;
    func_ov107_020c9264(*(int *)p, 11, 0);
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov140_020d1df8);
}
