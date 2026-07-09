int func_020219c4(short *arg0) {
    int r = 0;
    if (*arg0 == 1) r = *(int *)(arg0 + 2) << 0xc;
    else if (*arg0 != 2) r = *(int *)(arg0 + 2);
    return r;
}
