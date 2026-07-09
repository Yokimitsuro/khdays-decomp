extern int func_ov025_02084afc();
extern int func_ov025_02095cbc();
extern int func_02033b78();

void func_ov025_0209962c(int arg0) {
    int x = func_ov025_02084afc(arg0);
    if (*(int *)(x + 0x30) != 0) {
        return;
    }
    func_ov025_02095cbc(x, 1);
    func_02033b78(0, 1);
}
