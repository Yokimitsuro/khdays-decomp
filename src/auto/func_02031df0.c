void func_02031df0(int *arg0, int *arg1) {
    if (arg1 == (int *)*arg0) *arg0 = arg1[1];
    if ((int *)arg1[1] != (int *)0) *(int *)arg1[1] = *arg1;
    if (*arg1 != 0) *(int *)(*arg1 + 4) = arg1[1];
    *arg1 = 0;
    arg1[1] = 0;
}
