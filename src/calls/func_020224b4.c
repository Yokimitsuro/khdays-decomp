extern int func_020218a4(void *p);
extern void func_02021980(void *p, int x);
extern void func_02033bfc(void);

int func_020224b4(void *arg0) {
    int r = func_020218a4(arg0);
    func_02021980(arg0, r);
    func_02033bfc();
    return 1;
}
