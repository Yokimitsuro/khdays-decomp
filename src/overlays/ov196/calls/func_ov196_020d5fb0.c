extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_ov107_020c9ee8(int subject, int anim_id, int mode);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov196_020d5ffc(void);

void func_ov196_020d5fb0(char *obj) {
    char *p = *(char **)(obj + 4);
    *(int *)(p + 0x14) = 0;
    func_ov107_020c9264(*(int *)p, 12, 0);
    func_ov107_020c9ee8(*(int *)(*(char **)p + 0x3d0), 4, 0);
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov196_020d5ffc);
}
