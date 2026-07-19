int strncmp(const char *s1, const char *s2, unsigned n) {
    if (n != 0) {
        do {
            unsigned char c2 = (unsigned char)*s2++;
            unsigned char c1 = (unsigned char)*s1++;
            if (c1 != c2) {
                return (int)c1 - (int)c2;
            }
            if (c1 == 0) {
                break;
            }
        } while (--n != 0);
    }
    return 0;
}
