void func_ov162_020ce710(int **r0) {
    int *r3 = r0[1];
    int *r2 = ((int **)r3)[1];
    r2[0x5c / 4] |= 2;
    ((int *)((int *)r3[0])[0x3c4 / 4])[1] = 0;
}
