/* Ov023_FormatIndex -- format a 1-based index for display, picking the one- or two-digit
 * format string (gOv023Chair0Fmt below ten, gOv023ChairFmt from ten up).
 *
 * ⚠ It returns the address of its OWN 0x40-byte stack buffer, which is dead the moment it
 * returns. That is what the ROM does -- `add r0,sp,#0` right before the epilogue -- and callers
 * evidently read it before anything else reuses the stack. Kept as-is deliberately; do not
 * "fix" it into a static buffer, that would change the bytes. */
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern char gOv023Chair0Fmt[];
extern char gOv023ChairFmt[];

char *Ov023_FormatIndex(int index) {
    char buf[0x40];
    if (index + 1 < 10) {
        OS_SPrintf(buf, gOv023Chair0Fmt, index + 1);
    } else {
        OS_SPrintf(buf, gOv023ChairFmt, index + 1);
    }
    return buf;
}
