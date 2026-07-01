extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov194_020ce2c8(void);

void func_ov194_020ce27c(char *obj) {
    char *p = *(char **)(obj + 4);
    int val = *(int *)(p + 0x30) + *(int *)(*(char **)obj + 0x2c);
    *(int *)(p + 0x30) = val;
    if (val < 0x3000) return;
    func_ov107_020c9264(*(int *)p, 8, 0);
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov194_020ce2c8);
}
