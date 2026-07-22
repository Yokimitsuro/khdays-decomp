/* func_ov023_02086c90 -- format a 1-based index for display, picking the one- or two-digit
 * format string (data_ov023_0208a64c below ten, data_ov023_0208a658 from ten up).
 *
 * ⚠ It returns the address of its OWN 0x40-byte stack buffer, which is dead the moment it
 * returns. That is what the ROM does -- `add r0,sp,#0` right before the epilogue -- and callers
 * evidently read it before anything else reuses the stack. Kept as-is deliberately; do not
 * "fix" it into a static buffer, that would change the bytes. */
extern void OS_SPrintf(char *dst, const char *fmt, int n);
extern char data_ov023_0208a64c[];
extern char data_ov023_0208a658[];

char *func_ov023_02086c90(int index) {
    char buf[0x40];
    if (index + 1 < 10) {
        OS_SPrintf(buf, data_ov023_0208a64c, index + 1);
    } else {
        OS_SPrintf(buf, data_ov023_0208a658, index + 1);
    }
    return buf;
}
