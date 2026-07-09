extern int func_ov025_02084a7c();
extern int func_ov025_020884c8();
extern int func_ov025_0208843c();
extern void func_ov025_02088500();

void func_ov025_0208f144(int arg0) {
    int a = func_ov025_02084a7c();
    int e = func_ov025_020884c8(a, arg0);
    int local[2];
    local[0] = 0x78000;
    local[1] = *(int *)(e + 4) + 0x8000;
    func_ov025_02088500(a, func_ov025_0208843c(a, 3), local);
}
