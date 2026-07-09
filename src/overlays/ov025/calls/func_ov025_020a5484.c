extern int func_ov025_020894b0();
extern void func_ov025_0208951c();
extern void func_ov025_0208959c();

void func_ov025_020a5484(int arg0, unsigned int arg1, unsigned short arg2, unsigned short arg3) {
    int e = func_ov025_020894b0(arg0, arg1 & 0xffff);
    func_ov025_0208951c(arg0, e, arg2, arg3);
    func_ov025_0208959c(arg0, e);
}
