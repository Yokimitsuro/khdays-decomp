extern int func_0203c7e8();
extern int func_0203d194();
extern int func_ov107_020c68ec();
extern int func_ov107_020c9eac();

struct E { int a; int b; };

void func_ov183_020cfdd0(int *p) {
    int i;
    func_0203c7e8(p[0x384 / 4]);
    func_ov107_020c9eac(p[0x390 / 4]);
    for (i = 0; i < 3; i++) {
        func_0203c7e8(((struct E *)p[0x398 / 4])[i].a);
    }
    func_0203d194(p[0x398 / 4]);
    func_ov107_020c68ec(p);
}
