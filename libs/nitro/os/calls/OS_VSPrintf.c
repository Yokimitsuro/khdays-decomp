/* Unbounded vsprintf: forwards to the bounded core with a 0x7fffffff limit.
 * The callee's SDK name is misattributed (shape match, not identity). */
extern void *WM_EndKeySharing();

void *OS_VSPrintf(void *dst, const char *fmt, void *ap) {
    return WM_EndKeySharing(dst, 0x7fffffff, fmt, ap);
}
