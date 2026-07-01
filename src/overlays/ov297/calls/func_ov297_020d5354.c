extern void func_ov297_020d4168(char *obj);
extern void func_0203c634(void *obj, int idx, void *value);

void func_ov297_020d5354(char *obj) {
    char *p = *(char **)(obj + 0x4);
    func_ov297_020d4168(obj);
    if (*(char *)(*(int *)(p + 0x4) + 0xad) != 0) return;
    *(char *)(*(int *)p + 0x1c7) = 2;
    func_0203c634(obj, *(signed char *)(obj + 0x20), 0);
}
