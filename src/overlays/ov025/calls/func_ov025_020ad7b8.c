extern int func_ov025_02084b14();
extern int func_ov025_020acefc();

void func_ov025_020ad7b8(int arg0) {
    int x = func_ov025_02084b14(arg0);
    if (*(int *)(x + 0x180) != 0) {
        return;
    }
    *(int *)(x + 0x158) = 1;
    func_ov025_020acefc(x);
}
