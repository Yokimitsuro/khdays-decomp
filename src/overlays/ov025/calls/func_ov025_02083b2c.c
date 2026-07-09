extern int func_ov025_02083a9c();
extern int data_ov025_020b5744;

int func_ov025_02083b2c(int arg0, int *arg1) {
    int idx = func_ov025_02083a9c(arg0);
    int r = 0;
    if (idx != -1)
        r = *(int *)(*(int *)((char *)&data_ov025_020b5744 + 4) + idx * 4 + 0x95a4);
    if (arg1 != 0) *arg1 = idx;
    return r;
}
