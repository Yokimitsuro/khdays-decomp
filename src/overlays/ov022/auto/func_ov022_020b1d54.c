int func_ov022_020b1d54(unsigned char *arg0) {
    int r = 1;
    switch (*arg0) {
    case 0:
        r = 0;
        break;
    case 3:
        if (*(short *)(arg0 + 4) == -1) r = 0;
        break;
    }
    return r;
}
