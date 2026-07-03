extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov181_020ce908(void);

void func_ov181_020ce8d4(char *obj) {
    char *p = *(char **)(obj + 4);
    if (**(char **)(p + 0xc) != 0) return;
    *(int *)(p + 0x1c) = 0;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov181_020ce908);
}
