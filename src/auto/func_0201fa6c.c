/* strncat: appends at most `n` characters of `src` to `dst`, always NUL-terminating,
 * and returns `dst`. */
char *func_0201fa6c(char *dst, const char *src, unsigned int n) {
    char *p = dst;
    while (*p++ != 0) {
        ;
    }
    p--;
    if (n != 0) {
        do {
            if ((*p++ = *src++) == 0) {
                p--;
                break;
            }
        } while (--n != 0);
    }
    *p = 0;
    return dst;
}
