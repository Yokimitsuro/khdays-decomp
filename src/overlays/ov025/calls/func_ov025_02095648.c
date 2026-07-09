extern int func_ov025_02095544();

void func_ov025_02095648(int arg0, int arg1) {
    do {
        arg1 = (arg1 + 1) % 8;
    } while (func_ov025_02095544(arg0, arg1) == 0);
}
