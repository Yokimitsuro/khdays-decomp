extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov195_020d1464(void);

void func_ov195_020d1418(char *obj) {
    char *p = *(char **)(obj + 4);
    func_ov107_020c9264(*(int *)p, 4, 0);
    p[0x50] = 0;
    *(int *)(p + 0x30) = 0;
    p[0x51] = 0;
    p[0x53] = 0;
    *(int *)(p + 0x54) = 0;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov195_020d1464);
}
