extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov219_020d0b9c(void);

void func_ov219_020d0b60(char *obj) {
    char *p = *(char **)(obj + 4);
    func_ov107_020c9264(*(int *)p, 0, 1);
    *(int *)(p + 0x14) = 0x1000;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov219_020d0b9c);
}
