extern int func_ov025_02084b14();
extern int func_ov025_020af364();
extern void func_02035fb0();
extern void func_02035ffc();

void func_ov025_020af3ac(void) {
    int x = func_ov025_02084b14();
    if (func_ov025_020af364() == 0) {
        func_02035fb0((unsigned int *)(x + 0x10), 0, *(unsigned int *)(x + 0x2c), 0xffff0000, 100);
        func_02035ffc(x + 0x10);
        *(int *)(x + 500) = 1;
        *(int *)(x + 0x1f8) = 2;
    }
}
