/* strcpy: copy the NUL-terminated string src into dst, returning dst. */
char *func_0200ff20(char *dst, const char *src) {
    char *ret = dst;
    if (*src != 0) {
        do {
            *dst++ = *src++;
        } while (*src != 0);
    }
    *dst = 0;
    return ret;
}
