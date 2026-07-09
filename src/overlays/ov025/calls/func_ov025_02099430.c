extern int func_ov025_02084afc();
extern void func_ov025_0209522c();

void func_ov025_02099430(void) {
    int x = func_ov025_02084afc();
    if (*(int *)(x + 0x1e78) < 2) return;
    if (*(int *)(x + 0x30) != 0) return;
    if (*(int *)(x + 0x18) == 1) return;
    func_ov025_0209522c(x, 1, 1);
}
