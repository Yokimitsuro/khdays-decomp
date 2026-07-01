extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov135_020d1a84(void);

void func_ov135_020d1a38(char *obj) {
    char *p = *(char **)(obj + 0x4);
    if (*(char *)(*(int *)(p + 0x4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)p, 7, 1);
    *(int *)(p + 0x30) = 0;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov135_020d1a84);
}
