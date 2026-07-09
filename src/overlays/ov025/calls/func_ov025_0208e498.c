extern void func_02035fb0();
extern void func_02035ffc();

void func_ov025_0208e498(int arg0, int arg1, unsigned int arg2, unsigned int arg3) {
    if (arg1 < 0) arg1 = 0;
    if (arg1 >= 0xc) arg1 = 0xb;
    unsigned int *p = (unsigned int *)(arg0 + 0x1278 + arg1 * 0x20);
    func_02035fb0(p, 2, *(unsigned int *)(arg0 + arg1 * 0x20 + 0x1294), arg2, arg3);
    func_02035ffc((int)p);
}
