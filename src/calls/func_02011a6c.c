extern int *func_02011aa0(int a, int b);
int func_02011a6c(int param_1, void **param_2) {
    int *p = func_02011aa0(param_1, 0x5343524e);
    if (p != 0) {
        *param_2 = p + 2;
        return 1;
    }
    *param_2 = 0;
    return 0;
}
