/* Unbounded sprintf: hands the variadic tail to OS_VSPrintf.
 * The va_list is spelled out as the SDK's macro expands it -- align the address of the last
 * named parameter down to a word and step past it.  That is the ROM's
 * `add r2,sp,#0xc / bic r2,#3 / add r2,#4`, and taking `&fmt` is also what makes mwcc read
 * `fmt` back out of its homed slot instead of keeping the incoming register. */
extern void *OS_VSPrintf();

void *OS_SPrintf(char *dst, const char *fmt, ...) {
    return OS_VSPrintf(dst, fmt, (void *)(((unsigned int)&fmt & ~3u) + 4));
}
