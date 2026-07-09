extern int func_ov025_02090db0();
extern void func_ov025_02095544();
extern void func_02033b78();

void func_ov025_020956b0(int arg0, unsigned int arg1, int arg2, int arg3) {
    int s = *(int *)(arg0 + 0x30);
    if (s != 0) return;
    if (func_ov025_02090db0(arg0, arg1)) {
        if (arg1 != *(unsigned int *)(arg0 + 0x70)) {
            func_ov025_02095544(arg0, arg1);
            func_02033b78(0, 2);
        }
    }
}
