extern int func_020358f4(int kind, int b);
extern int data_0204c240;
extern int data_0204c248;

int func_ov022_02095648(int obj) {
    int r = 0x4cd;
    int e = *(int *)(obj + 0x328);
    int u = func_020358f4(*(unsigned char *)(e + 9), 0x52);
    unsigned int v;
    if (u > 0) r = u * (0x800 - r) + r;
    v = *(unsigned short *)(e + 0x16);
    r -= *(unsigned char *)(obj + 0x335) * 0x19a;
    r *= v;
    if (r < 0x1000) r = 0x1000;
    if (*(unsigned char *)&data_0204c240 & 4) {
        switch (*(unsigned char *)((char *)&data_0204c248 + 8)) {
        case 0: r = 0; break;
        case 1: break;
        case 2: r = v << 0xb; break;
        }
    }
    return (r + 0xfff) >> 0xc;
}
