extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov182_020cfe24(void);

void func_ov182_020cfde0(char *obj) {
    char *p = *(char **)(obj + 4);
    int val = *(int *)(p + 0x1c) + *(int *)(*(char **)obj + 0x2c);
    *(int *)(p + 0x1c) = val;
    if (val <= 0x800) return;
    *(int *)(p + 0x70) = 0x300;
    p[0x50] = 0;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov182_020cfe24);
}
