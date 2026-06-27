extern int func_0201f908(void *a);
extern int WM_EndKeySharing_0x0202019c(void *a, void *b, int c);

int func_02024fe8(unsigned char *arg0, void *arg1) {
    int i;
    unsigned char *p;
    int r0;
    unsigned short count;

    r0 = func_0201f908(arg1);
    count = (unsigned short)(*(unsigned short *)(arg0 + 2) & 0x1ff);
    p = (arg0 + 0x10) + (((unsigned int)((count + 1) / 2) << 17) >> 15);
    p += count * 4;
    for (i = 0; i < count; i++) {
        if (WM_EndKeySharing_0x0202019c(p, arg1, r0) == 0) {
            return i;
        }
        p += 8;
    }
    return -1;
}
