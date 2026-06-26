extern int func_020200c8();
extern int func_020200e4();
extern int func_02023660();

int func_ov004_0204cb30(int *a, char *b) {
    char *p;
    int n;

    n = (func_020200c8(b) + 1) * 2;
    p = (char *)func_02023660(n);
    func_020200e4(p, b);
    if (a) {
        *a = (int)(b + n);
    }
    return (int)p;
}
