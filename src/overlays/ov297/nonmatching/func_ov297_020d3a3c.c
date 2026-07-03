extern void func_0203c7e8();
extern void func_ov107_020c68ec(char *obj);

void func_ov297_020d3a3c(char *obj) {
    int i;
    func_0203c7e8(*(int **)(obj + 0x384));
    func_0203c7e8(*(int *)(obj + 0x388));
    for (i = 0; i < 2; i++) {
        func_0203c7e8(*(int **)(obj + i * 8 + 0x398));
    }
    func_ov107_020c68ec(obj);
}
