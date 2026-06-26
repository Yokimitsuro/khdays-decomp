void func_ov025_02089544(int *r0, int r1) {
    void (*fp)(int) = (void (*)(int))r0[0xf];
    if (fp == 0) {
        return;
    }
    fp(r1);
}
