int strlen(const char *s) {
    int n = -1;
    char c;
    do {
        c = *s++;
        n++;
    } while (c != 0);
    return n;
}
