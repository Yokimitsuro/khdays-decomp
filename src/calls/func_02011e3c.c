extern int func_02011c44(int *, unsigned int);

int func_02011e3c(int *param_1, unsigned int param_2) {
    int result = func_02011c44(param_1, param_2);
    if (result != 0) {
        param_1[4] = 0;
    }
    return result;
}
