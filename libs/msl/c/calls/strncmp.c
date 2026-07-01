int strncmp(const unsigned char *s1, const unsigned char *s2, unsigned int n) {
    if (n != 0) {
        do {
            unsigned char b = *s2++;
            unsigned char a = *s1++;
            if (a != b) return (int)a - (int)b;
            if (a == 0) break;
        } while (--n != 0);
    }
    return 0;
}
