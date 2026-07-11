extern int func_02021980(void *a);
extern int func_02033cc8(int x);
extern void func_020219b4(void *a, int b);
extern void func_020335ec(int x);
extern unsigned char data_020425e8;

int func_020223dc(void *obj, int arg1) {
    int r4 = func_02021980(obj);
    if (func_02033cc8(r4) != 0) {
        func_020219b4(obj, r4);
        return 0;
    }
    data_020425e8 = r4;
    func_020335ec(r4 & 0xff);
    return 1;
}
