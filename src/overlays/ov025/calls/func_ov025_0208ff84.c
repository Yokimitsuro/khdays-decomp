extern int func_ov025_0208843c();
extern void func_ov025_020887c0();
extern void func_ov025_0208884c();

void func_ov025_0208ff84(int arg0, int arg1, int arg2) {
    int r = func_ov025_0208843c(arg0, arg1);
    func_ov025_020887c0(arg0, r, arg2 == 0);
    func_ov025_0208884c(arg0, r, arg2);
}
