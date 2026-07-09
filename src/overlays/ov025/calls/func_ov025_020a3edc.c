extern int func_ov025_02084b14();
extern int func_ov025_020a13d8();
extern int func_02033b78();

void func_ov025_020a3edc(int arg0) {
    int x = func_ov025_02084b14(arg0);
    if (*(int *)(x + 8) != 0) {
        return;
    }
    func_ov025_020a13d8(x, 1, 0x64);
    func_02033b78(0, 2);
}
