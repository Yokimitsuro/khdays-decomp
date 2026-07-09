extern int func_ov025_02084afc();
extern int func_ov025_020998c8();
extern int func_ov025_0208f37c();

void func_ov025_02099990(int arg0) {
    int x = func_ov025_02084afc(arg0);
    if (*(int *)(x + 0x30) != 0) {
        return;
    }
    func_ov025_020998c8(x, 0);
    func_ov025_0208f37c(x, 0);
}
