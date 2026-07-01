extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_ov147_020cc9c0(int obj, int arg);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov147_020cdb90(void);

void func_ov147_020cdb50(char *obj) {
    char *p = *(char **)(obj + 4);
    func_ov107_020c9264(*(int *)p, 2, 0);
    func_ov147_020cc9c0(*(int *)p, 0);
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov147_020cdb90);
}
