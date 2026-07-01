extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov133_020d2d94(void);

void func_ov133_020d2d50(char *obj) {
    char *p = *(char **)(obj + 0x4);
    if (**(char **)(p + 0x48) != 0) return;
    func_ov107_020c9264(*(int *)(p + 0x0), 2, 1);
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov133_020d2d94);
}
