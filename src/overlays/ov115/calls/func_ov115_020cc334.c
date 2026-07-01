extern void func_0203c7e8(int v);
extern void func_0203d194(int v);
extern void func_ov107_020c68ec(char *a);

void func_ov115_020cc334(char *a) {
    int i;
    func_0203c7e8(*(int *)(a + 0x384));
    for (i = 0; i < 7; i++) {
        func_0203c7e8(*(int *)(*(char **)(a + 0x39c) + i * 8));
    }
    func_0203d194(*(int *)(a + 0x39c));
    func_ov107_020c68ec(a);
}
