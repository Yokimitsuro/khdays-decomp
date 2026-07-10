int func_ov022_020b1cec(unsigned char *p, int val) {
    int r = 0;
    switch (*p) {
    case 0:
    case 1:
        *(unsigned short *)(p + 2) = val;
        *p = 1;
        break;
    case 2:
        if (*(short *)(p + 2) != val) *(unsigned short *)(p + 4) = val;
        break;
    case 3:
        if (*(short *)(p + 2) != val) *(unsigned short *)(p + 4) = val;
        else r = 1;
        break;
    case 4:
        *(unsigned short *)(p + 4) = val;
        break;
    }
    return r;
}
