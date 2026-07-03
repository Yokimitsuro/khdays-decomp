extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov250_020d27a0(void);

void func_ov250_020d276c(char *obj) {
    char *p = *(char **)(obj + 4);
    if (**(char **)(p + 0xc) != 0) return;
    *(int *)(p + 0x1c) = 0;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov250_020d27a0);
}
