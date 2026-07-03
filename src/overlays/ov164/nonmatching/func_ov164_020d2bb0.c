extern void func_0203b9fc(void *p, int a, int b, int c);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov164_020d2bf4(void);

void func_ov164_020d2bb0(char *obj) {
    char *p = *(char **)(*(char **)(obj + 0x4) + 0x4);
    if (p[0xad] != 0) return;
    func_0203b9fc(p, 0, 1, 1);
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov164_020d2bf4);
}
