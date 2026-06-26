int func_020255d4(int *r0, int r1, int r2)
{
    int *p = ((int **)(r0 + r1))[2];
    return p ? ((int **)(p + r2))[1] : 0;
}
