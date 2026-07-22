/* Bounded sprintf; same va_list spelling as OS_SPrintf.  The core's SDK name is one of the
 * misattributed ones. */
extern void *WM_EndKeySharing();

void *OS_SNPrintf(char *dst, unsigned int len, const char *fmt, ...) {
    return WM_EndKeySharing(dst, len, fmt, (void *)(((unsigned int)&fmt & ~3u) + 4));
}
