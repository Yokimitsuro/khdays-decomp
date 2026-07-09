extern int func_ov025_02084a7c();
extern int func_ov025_0208843c();
extern void func_ov025_0208884c();
extern void func_ov025_02088928();

void func_ov025_0209bcd8(int arg0, unsigned int arg1) {
    int a = func_ov025_02084a7c();
    int e = func_ov025_0208843c(a, arg0);
    if ((int)arg1 >= 0) {
        func_ov025_0208884c(a, e, 1);
        func_ov025_02088928(a, e, arg1 & 0xffff);
        return;
    }
    func_ov025_0208884c(a, e, 0);
}
