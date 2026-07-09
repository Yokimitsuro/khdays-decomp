extern void func_ov025_02095cbc();
extern void func_02033b78();

void func_ov025_020998c8(int arg0, int arg1, int arg2, int arg3) {
    *(int *)(arg0 + 0x20) = arg1;
    if (*(int *)(arg0 + 0xa4) == 1)
        func_ov025_02095cbc(arg0, 2, arg2, arg3);
    else
        func_ov025_02095cbc(arg0, 5, arg2, arg3);
    func_02033b78(0, 1);
}
