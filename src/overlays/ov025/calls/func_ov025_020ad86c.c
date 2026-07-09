extern int func_ov025_02084b14();
extern void func_ov025_020ac4d8();
extern void func_ov025_020a9bc4();

void func_ov025_020ad86c(void) {
    int x = func_ov025_02084b14();
    if (*(int *)(x + 0x150) != 0 && *(int *)(x + 0x154) == 0) return;
    if (*(int *)(x + 0x180) == 0) return;
    if (*(int *)(x + 0x184) == 0) func_ov025_020ac4d8(x, 1);
    func_ov025_020a9bc4();
}
