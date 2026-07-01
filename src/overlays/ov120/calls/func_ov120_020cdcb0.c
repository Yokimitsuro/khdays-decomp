extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov120_020cdcf0(void);

void func_ov120_020cdcb0(char *obj) {
    char *p = *(char **)(obj + 4);
    int val = *(int *)(p + 0x40) + *(int *)(*(char **)obj + 0x2c);
    *(int *)(p + 0x40) = val;
    if (val <= 0x3000) return;
    *(char *)(*(int *)(p + 0x4) + 0xa8) = 0;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov120_020cdcf0);
}
