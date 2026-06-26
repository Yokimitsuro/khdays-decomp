void *func_02010314(int *r0, int *r1, int *r2)
{
    int *r3;

    r1[2] = (int)r2;
    if (r2 != 0) {
        r3 = (int *)r2[3];
        r2[3] = (int)r1;
    } else {
        r3 = (int *)r0[0];
        r0[0] = (int)r1;
    }
    r1[3] = (int)r3;
    if (r3 != 0) {
        r3[2] = (int)r1;
    } else {
        r0[1] = (int)r1;
    }
    return r1;
}
