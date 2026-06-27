extern void *func_020218a4(void *arg);

int func_02021980(void *arg) {
    short *p = (short *)func_020218a4(arg);
    int r = 0;
    if (*p == 1) r = ((int *)p)[1];
    return r;
}
