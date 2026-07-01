extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_ov276_020d0cdc(int obj, int arg);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov276_020d2a60(void);

void func_ov276_020d2a20(char *obj) {
    char *p = *(char **)(obj + 4);
    func_ov107_020c9264(*(int *)p, 2, 1);
    func_ov276_020d0cdc(*(int *)p, 1);
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov276_020d2a60);
}
