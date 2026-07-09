extern int func_ov025_02088544();
extern void func_ov025_02088500();

void func_ov025_02088564(int arg0, int arg1, int *arg2) {
    int *p = (int *)func_ov025_02088544(arg0, arg1);
    int local[2];
    local[0] = arg2[0] + p[0];
    local[1] = arg2[1] + p[1];
    func_ov025_02088500(arg0, arg1, local);
}
