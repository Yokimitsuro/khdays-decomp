char *strncpy(char *dst, const char *src, unsigned n) {
    char *d = dst;
    char *p;
    if (n == 0) {
        return dst;
    }
    do {
        p = d;
        *d++ = *src++;
        if (*p == 0) {
            while (--n != 0) {
                *d++ = 0;
            }
            return dst;
        }
    } while (--n != 0);
    return dst;
}
