/* Formats a pending text into the ov106 context and flags it. */

extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int data_ov106_020b8b60;

void Ov106_SetPendingText(const char *fmt) {
    char *base = (char *)*(int *)&data_ov106_020b8b60;
    *(unsigned short *)(base + 0x8e44) |= 2;
    OS_SPrintf((char *)*(int *)&data_ov106_020b8b60 + 0x8e50, fmt);
}
