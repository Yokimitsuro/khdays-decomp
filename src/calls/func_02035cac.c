extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

extern char *data_0204c4f0[];
extern char data_0204c6b4[];
extern char data_0204c714[];

void func_02035cac(int a, int b) {
    char *p = data_0204c4f0[2];
    char *dst;
    char *src;
    int i;
    if (a) {
        dst = data_0204c6b4;
        for (i = 0, src = p; i < 24; i++) {
            MI_CpuCopy8(src, dst, 4);
            dst += 4;
            src += 4;
        }
    }
    if (b) {
        dst = data_0204c714;
        i = 0;
        p += 0x60;
        for (; i < 15; i++) {
            MI_CpuCopy8(p, dst, 2);
            dst += 2;
            p += 2;
        }
    }
}
