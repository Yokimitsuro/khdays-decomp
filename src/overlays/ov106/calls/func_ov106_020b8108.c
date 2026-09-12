extern void OS_SPrintf(char *dst, const char *fmt);
extern int data_ov106_020b8b60;

void func_ov106_020b8108(const char *fmt) {
    char *base = (char *)*(int *)&data_ov106_020b8b60;
    *(unsigned short *)(base + 0x8e44) |= 2;
    OS_SPrintf((char *)*(int *)&data_ov106_020b8b60 + 0x8e50, fmt);
}
