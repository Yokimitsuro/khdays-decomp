int func_020026b0(int r0, int *r1)
{
    int *prev = (int *)r1[4];
    int *next = (int *)r1[5];

    if (prev == 0)
        *(int **)(r0 + 0x8c) = next;
    else
        prev[5] = (int)next;

    if (next == 0)
        *(int **)(r0 + 0x88) = prev;
    else
        next[4] = (int)prev;

    return r0;
}
