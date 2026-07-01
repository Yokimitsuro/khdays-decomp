int func_ov008_020512e0(void *fp, void *arg) {
    int r = 0;
    if (fp) {
        ((void (*)(void *))fp)(arg);
        r = 1;
    }
    return r;
}
