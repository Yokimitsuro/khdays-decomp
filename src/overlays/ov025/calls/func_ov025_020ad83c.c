extern int func_ov025_02084b14();
extern int func_ov025_020aa0a4();
extern int func_02033b78();

void func_ov025_020ad83c(void) {
    int x = func_ov025_02084b14();
    if (*(int *)(x + 0x180) != 0) {
        return;
    }
    func_ov025_020aa0a4(func_ov025_02084b14(), 2);
    func_02033b78(0, 0);
}
