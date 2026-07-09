extern int func_ov025_02084afc();
extern int func_ov025_0209522c();

void func_ov025_02099400(int arg0) {
    int x = func_ov025_02084afc(arg0);
    if (*(int *)(x + 0x30) != 0) {
        return;
    }
    if (*(int *)(x + 0x18) == 0) {
        return;
    }
    func_ov025_0209522c(x, 0, 1);
}
