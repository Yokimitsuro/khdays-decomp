extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov270_020d50a0(void);

void func_ov270_020d5054(char *obj) {
    char *p = *(char **)(obj + 4);
    func_ov107_020c9264(*(int *)p, 4, 0);
    p[0x50] = 0;
    *(int *)(p + 0x30) = 0;
    p[0x51] = 0;
    p[0x53] = 0;
    *(int *)(p + 0x54) = 0;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov270_020d50a0);
}
