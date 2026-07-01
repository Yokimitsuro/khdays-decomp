extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_ov148_020d0600(int obj, int arg);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov148_020d17d0(void);

void func_ov148_020d1790(char *obj) {
    char *p = *(char **)(obj + 4);
    func_ov107_020c9264(*(int *)p, 2, 0);
    func_ov148_020d0600(*(int *)p, 0);
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov148_020d17d0);
}
