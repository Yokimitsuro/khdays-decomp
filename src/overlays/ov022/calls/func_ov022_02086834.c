extern void func_ov022_020848bc(unsigned int *arg0, int arg1);
void func_ov022_02086834(int arg0, int arg1) {
    unsigned int *p = *(unsigned int **)(arg0 + 0x20);
    if (arg1 != 0) {
        *p |= 4;
        p[1] |= 2;
        p[0x8c] = 1;
        return;
    }
    *p &= ~4;
    func_ov022_020848bc(p + 1, 2);
    p[0x8c] = 0;
}
