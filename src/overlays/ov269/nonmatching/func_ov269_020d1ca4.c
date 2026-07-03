extern void func_0203c7e8(int *obj);
extern void func_0203d194(int obj);
extern void func_ov107_020c9eac(int v);
extern void func_ov107_020c68ec(char *obj);

void func_ov269_020d1ca4(char *obj) {
    int i;
    func_0203c7e8(*(int **)(obj + 0x384));
    func_ov107_020c9eac(*(int *)(obj + 0x3d0));
    for (i = 0; i < 3; i++) {
        func_0203c7e8(*(int **)(*(char **)(obj + 0x3d4) + i * 8));
    }
    func_0203d194(*(int *)(obj + 0x3d4));
    func_ov107_020c68ec(obj);
}
