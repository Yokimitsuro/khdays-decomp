int func_0202fd90(int r0, int *r1)
{
    int *r2 = (int *)r1[8];

    if (r0 != 1 && r0 != 2) {
        return r0;
    }
    r0 = r2[r0 - 1];
    r1[7] = r0;
    return r0;
}
