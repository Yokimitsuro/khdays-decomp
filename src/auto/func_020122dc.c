void func_020122dc(int *p, short val) {
    if (*p == 1) {
        unsigned short *h = (unsigned short *)p;
        h[9] |= 4;
        h[8] = val;
    }
}
