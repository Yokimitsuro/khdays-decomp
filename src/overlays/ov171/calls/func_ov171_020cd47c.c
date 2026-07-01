extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern int func_02023eb4(unsigned int mul);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov171_020cd4c0(void);

void func_ov171_020cd47c(char *obj) {
    char *p = *(char **)(obj + 4);
    func_ov107_020c9264(*(int *)p, 1, 1);
    *(int *)(p + 0x54) = func_02023eb4(1) + 0x78;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov171_020cd4c0);
}
