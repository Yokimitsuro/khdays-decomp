extern void func_0203c7e8(int *obj);
extern void func_ov107_020c9eac(int v);
extern void func_ov107_020c68ec(char *obj);

void func_ov220_020d1c1c(char *obj) {
    int i;
    func_0203c7e8(*(int **)(obj + 0x384));
    func_ov107_020c9eac(*(int *)(obj + 0x394));
    for (i = 0; i < 3; i++) {
        func_0203c7e8(*(int **)(obj + i * 8 + 0x3c4));
    }
    func_ov107_020c68ec(obj);
}
