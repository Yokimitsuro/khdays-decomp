int func_ov002_02067150(unsigned short *p) {
    int count = 1;
    if (*p != 0) {
        do {
            if (*p == 0xa) {
                count++;
            }
            p++;
        } while (*p != 0);
    }
    return count;
}
