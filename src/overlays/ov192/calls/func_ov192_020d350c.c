extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov192_020d3558(void);

void func_ov192_020d350c(char *obj) {
    char *p = *(char **)(obj + 4);
    func_ov107_020c9264(*(int *)p, 4, 0);
    *(int *)(p + 0x2c) = 0;
    p[0x38] = 0;
    p[0x39] &= ~0x2;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov192_020d3558);
}
