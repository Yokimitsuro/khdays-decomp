extern void func_ov129_020d5c58(char *obj);
extern void func_0203c634(void *obj, int idx, void *value);

void func_ov129_020d6564(char *obj) {
    char *p = *(char **)(obj + 0x4);
    func_ov129_020d5c58(obj);
    if (*(char *)(*(int *)(p + 0x4) + 0xad) != 0) return;
    *(char *)(*(int *)p + 0x1c7) = 4;
    func_0203c634(obj, *(signed char *)(obj + 0x20), 0);
}
