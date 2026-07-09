void func_ov022_020b152c(unsigned char *arg0) {
    unsigned char v = *arg0;
    if ((v & 1) != 0) {
        *arg0 = v | 4;
        return;
    }
    if ((v & 2) != 0) {
        *arg0 = 0;
        arg0[3] = 0;
    }
}
