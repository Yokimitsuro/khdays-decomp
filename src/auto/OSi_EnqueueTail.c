void OSi_EnqueueTail(int *r0, int *r1) {
    int *r2 = (int *)r0[0x8c / 4];
    if (r2 == 0)
        r0[0x88 / 4] = (int)r1;
    else
        r2[0x10 / 4] = (int)r1;
    r1[0x14 / 4] = (int)r2;
    r1[0x10 / 4] = 0;
    r0[0x8c / 4] = (int)r1;
}
