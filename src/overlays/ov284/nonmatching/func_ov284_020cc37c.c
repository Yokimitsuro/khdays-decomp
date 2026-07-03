extern void func_0203c7e8();
extern void func_0203d194(int obj);
extern void func_ov107_020c68ec(char *obj);

void func_ov284_020cc37c(char *obj) {
    int i;
    func_0203c7e8(*(int **)(obj + 0x384));
    func_0203c7e8(*(int *)(obj + 0x3ac));
    for (i = 0; i < 4; i++) {
        func_0203c7e8(*(int **)(*(char **)(obj + 0x3b0) + i * 8));
    }
    func_0203d194(*(int *)(obj + 0x3b0));
    func_ov107_020c68ec(obj);
}
