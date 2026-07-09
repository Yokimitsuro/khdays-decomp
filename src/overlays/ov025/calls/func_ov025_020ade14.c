extern int func_ov025_02084a8c();
extern int func_ov025_0208843c();
extern void func_ov025_02088564();

void func_ov025_020ade14(int arg0) {
    int a = func_ov025_02084a8c();
    int local[2];
    local[0] = 0;
    local[1] = ((*(int *)(arg0 + 0x2c8) * 0x10 - *(int *)(arg0 + 0x2d0)) - 0x28) * 0x1000;
    func_ov025_02088564(a, func_ov025_0208843c(a, 1), local);
}
