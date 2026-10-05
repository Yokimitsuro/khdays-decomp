/* Bounded sprintf; same va_list spelling as OS_SPrintf.  The core's SDK name is one of the
 * misattributed ones. */
extern int Text_VSNPrintf(char *dst, unsigned int len, const char *fmt, void *vlist);

int OS_SNPrintf(char *dst, unsigned int len, const char *fmt, ...) {
    return Text_VSNPrintf(dst, len, fmt, (void *)(((unsigned int)&fmt & ~3u) + 4));
}
