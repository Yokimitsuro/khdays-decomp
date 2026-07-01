int func_ov008_02074b10(unsigned short *str) {
    int count;
    unsigned short c;
    if (str == 0 || (c = *str) == 0) return 0;
    count = 2;
    while (c != 0) {
        if (c == 0xa) count += 2;
        c = *++str;
    }
    return count;
}
