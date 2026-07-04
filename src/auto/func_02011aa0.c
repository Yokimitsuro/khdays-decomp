int *func_02011aa0(int param_1, int param_2) {
    unsigned short i = 0;
    int *p = (int *)(param_1 + *(unsigned short *)(param_1 + 0xc));
    while (i < *(unsigned short *)(param_1 + 0xe)) {
        if (*p == param_2) return p;
        p = (int *)((int)p + p[1]);
        i++;
    }
    return 0;
}
