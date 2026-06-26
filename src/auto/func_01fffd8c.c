int func_01fffd8c(int *r0)
{
    int *node;

    node = (int *)((int *)r0[9])[1];
    r0[9] = (int)node;
    if (node == r0 + 4) {
        return 0;
    }
    return node[3];
}
