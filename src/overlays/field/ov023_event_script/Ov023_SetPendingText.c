/* Ov023_SetPendingText -- raise the "text pending" bit (2) of the status halfword at +0x8758c and
 * copy the caller's string into the buffer just past it (+0x87598). The scene root is re-read
 * from the global for the second access, as the ROM does. */
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int data_ov023_0208a784;

void Ov023_SetPendingText(const char *fmt) {
    char *base = (char *)*(int *)((char *)&data_ov023_0208a784 + 4);
    *(unsigned short *)(base + 0x8758c) |= 2;
    OS_SPrintf((char *)*(int *)((char *)&data_ov023_0208a784 + 4) + 0x87598, fmt);
}
