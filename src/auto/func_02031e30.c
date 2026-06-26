void func_02031e30(int **r0, int **r1, int **r2) {
    int *node;
    r2[1] = (int *)r1;
    node = r1[0];
    r2[0] = node;
    if (node == 0) {
        r0[0] = (int *)r2;
    } else {
        node[1] = (int)r2;
    }
    r1[0] = (int *)r2;
}
