extern void func_0203c7e8(int *obj);
extern void func_0203d194(int obj);
extern void func_ov107_020c68ec(char *obj);

void func_ov124_020cfe94(char *obj) {
    int i;
    func_0203c7e8(*(int **)(obj + 0x384));
    for (i = 0; i < 2; i++) {
        func_0203c7e8(*(int **)(*(char **)(obj + 0x398) + i * 8));
    }
    func_0203d194(*(int *)(obj + 0x398));
    func_ov107_020c68ec(obj);
}
