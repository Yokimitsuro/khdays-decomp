extern int func_02030694(void);
int func_ov022_0208b1c8(int arg0, int *arg1, int arg2) {
    int r = 0;
    *arg1 += arg2;
    if (func_02030694()) {
        if (*arg1 >= 0x3000) r = 1;
    } else {
        r = 1;
    }
    if (r) *(char *)(arg1 + 0x53) = 0;
    return r;
}
