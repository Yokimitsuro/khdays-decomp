void func_ov026_020835c4(int *r0, int r1) {
    void (*fp)(int) = (void (*)(int))r0[0xf];
    if (fp == 0) {
        return;
    }
    fp(r1);
}
