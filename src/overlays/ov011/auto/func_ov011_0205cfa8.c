int func_ov011_0205cfa8(unsigned short *s, int arg1) {
    unsigned short c;
    if (s == 0) {
        return 0;
    }
    c = *s;
    if (c == 0x3c) {
        return 1;
    }
    if (c != 0) {
        do {
            s++;
        } while (*s != 0);
    }
    return s[-1] == 0x3e || arg1 == 2;
}
