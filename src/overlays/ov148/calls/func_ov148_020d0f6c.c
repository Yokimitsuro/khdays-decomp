extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov148_020d0fa8(void);

void func_ov148_020d0f6c(char *obj) {
    char *p = *(char **)(obj + 4);
    func_ov107_020c9264(*(int *)p, 1, 0);
    *(int *)(p + 0x40) = 0x2000;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov148_020d0fa8);
}
