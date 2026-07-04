extern int *NNSi_AllocFromHeadOfExpHeap(void *a, int b, int c);

int func_02010c2c(int param_1, int param_2) {
    int old = *(int *)(param_1 + 0x24);
    int *node = NNSi_AllocFromHeadOfExpHeap((void *)(param_1 + 0x24), 0x10, 4);
    if (node != 0) {
        node[0] = param_2;
        node[1] = old;
        node[2] = *(int *)(param_1 + 0x28);
        node[3] = *(int *)(param_1 + 0x2c);
        *(int **)(param_1 + 0x2c) = node;
        return 1;
    }
    return 0;
}
