extern int func_ov025_0208969c();
extern void func_ov025_020897b4();
extern void func_ov025_020896fc();

void func_ov025_020a9ad4(int arg0, unsigned int arg1, unsigned short arg2, unsigned short arg3) {
    int e = func_ov025_0208969c(arg0, arg1 & 0xffff);
    func_ov025_020897b4(arg0, e, arg2, arg3);
    func_ov025_020896fc(arg0, e, 1);
}
