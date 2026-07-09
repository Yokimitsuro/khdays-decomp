extern int func_02013768();
extern int func_ov025_02084cb4();
extern int func_ov025_02084c84();

void func_ov025_0208d408(int *arg0, int arg1) {
    if (arg0 != 0 && arg1 != 0) {
        int r = func_02013768((int *)arg0[8], arg0[9], arg1, 0);
        if (r > 0x70) r = func_ov025_02084cb4();
        else r = func_ov025_02084c84();
        if (r != *arg0) {
            *arg0 = r;
            arg0[8] = r;
        }
    }
}
