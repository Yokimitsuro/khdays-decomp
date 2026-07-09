extern int func_ov025_02084afc();
extern int func_ov025_020afd18();
extern void func_02033b78();
extern void func_ov025_02084798();

void func_ov025_0209e128(void) {
    int x = func_ov025_02084afc();
    if (func_ov025_020afd18() != 0) return;
    func_02033b78(0, 3);
    func_ov025_02084798(0, -1);
    *(unsigned int *)(x + 0xc) &= 0xffffff0f;
}
