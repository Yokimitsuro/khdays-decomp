int func_020200c8(unsigned short *arg0) {
    int n = -1;
    unsigned short c;
    do {
        c = *arg0++;
        n++;
    } while (c != 0);
    return n;
}
