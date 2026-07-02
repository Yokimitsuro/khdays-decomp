extern void func_0202b1c0(void *);

void func_0202ba18(unsigned char *param_1) {
    if ((param_1[8] & 4) == 0) {
        return;
    }
    func_0202b1c0(param_1 + 0xc);
    param_1[8] &= ~4;
}
