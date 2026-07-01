void func_ov005_0204d4c8(int *r0, int r1) {
    void (*fp)(int) = (void (*)(int))r0[0xf];
    if (fp == 0) {
        return;
    }
    fp(r1);
}
