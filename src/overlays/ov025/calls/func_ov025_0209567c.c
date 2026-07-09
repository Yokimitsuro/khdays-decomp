extern int func_ov025_02095544();

void func_ov025_0209567c(int arg0, int arg1) {
    do {
        arg1 = (arg1 + 7) % 8;
    } while (func_ov025_02095544(arg0, arg1) == 0);
}
