extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov114_020cdc48(void);

void func_ov114_020cdc04(char *obj) {
    char *p = *(char **)(obj + 4);
    int val = *(int *)(p + 0x44) + *(int *)(*(char **)obj + 0x2c);
    *(int *)(p + 0x44) = val;
    if (val <= 0x800) return;
    *(int *)(p + 0x68) = 0x300;
    p[0x49] = 0;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov114_020cdc48);
}
