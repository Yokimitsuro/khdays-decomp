extern void func_ov127_020cc468(char *obj);
extern void func_0203c634(void *obj, int idx, void *value);

void func_ov127_020cd2c0(char *obj) {
    char *p = *(char **)(obj + 0x4);
    func_ov127_020cc468(obj);
    if (*(char *)(*(int *)(p + 0x4) + 0xad) != 0) return;
    *(char *)(*(int *)p + 0x1c7) = 2;
    func_0203c634(obj, *(signed char *)(obj + 0x20), 0);
}
