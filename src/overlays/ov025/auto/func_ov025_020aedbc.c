int func_ov025_020aedbc(unsigned short *str) {
    int count = 1;
    unsigned short c = *str;
    if (c != 0) {
        do {
            if (c == 0xa) count++;
            c = *++str;
        } while (c != 0);
    }
    return count;
}
