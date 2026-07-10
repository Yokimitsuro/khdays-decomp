extern int func_ov002_0206aaa0(void);
extern int func_ov022_02083f0c(void);
extern int func_ov022_02083f5c(void);
extern int func_ov002_0204cb18(int arg0);

int func_ov022_02087344(void) {
    int a;
    if (func_ov002_0206aaa0() == 0) return 0;
    a = func_ov022_02083f0c();
    if (a == -1) return 0;
    if (func_ov022_02083f5c() == -1) return 0;
    return func_ov002_0204cb18(a) != 0;
}
