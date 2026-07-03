extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov184_020d3074(void);

void func_ov184_020d3040(char *obj) {
    char *p = *(char **)(obj + 4);
    if (**(char **)(p + 0xc) != 0) return;
    *(int *)(p + 0x1c) = 0;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov184_020d3074);
}
