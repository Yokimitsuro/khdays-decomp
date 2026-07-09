extern int func_ov025_02084afc();
extern void func_ov025_0209522c();

void func_ov025_02099470(void) {
    int x = func_ov025_02084afc();
    if (*(int *)(x + 0x1e78) < 3) return;
    if (*(int *)(x + 0x30) != 0) return;
    if (*(int *)(x + 0x18) == 2) return;
    func_ov025_0209522c(x, 2, 1);
}
