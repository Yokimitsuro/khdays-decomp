void *func_02012880(void *base, int a, int b) {
    int i;
    unsigned short *p = (unsigned short *)base;
    for (i = 0; i < 4; i++) {
        if (a <= p[0] && b <= p[1]) {
            return (char *)base + i * 6;
        }
        p += 3;
    }
    return (char *)base + 0x12;
}
