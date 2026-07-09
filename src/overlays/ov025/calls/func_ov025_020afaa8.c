extern int func_ov025_02084b14();
extern void func_ov025_020b0888();
extern void func_ov025_020b0864();

void func_ov025_020afaa8(int arg0) {
    int base = func_ov025_02084b14();
    func_ov025_020b0888(base + 0x200);
    int i = 0;
    if (arg0 * 2 <= 0) return;
    do {
        func_ov025_020b0864(base + 0x200);
        i++;
    } while (i < arg0 * 2);
}
