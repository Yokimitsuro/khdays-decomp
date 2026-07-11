extern int func_02021980(void *a, int b);
extern int func_02021994(void *a, int b);
extern int func_02020400(int a, int b);
extern int func_ov002_02076468(int a);
extern void func_ov014_020800a8(int a, unsigned short b, unsigned short c, unsigned short d,
                                 int e, void *f, int g, int h);

int func_ov014_02080718(void *arg1, int arg2) {
    int t0 = func_02021980(arg1, arg2);
    int r7 = func_02021980(arg1, arg2 + 8);
    int t14 = func_02021980(arg1, arg2 + 0x10);
    unsigned int r6 = *(unsigned int *)((char *)arg2 + 0x1c);
    int buf[3];
    buf[0] = func_02021994(arg1, arg2 + 0x20);
    buf[1] = func_02021994(arg1, arg2 + 0x28);
    buf[2] = func_02021994(arg1, arg2 + 0x30);
    int t18 = func_02021980(arg1, arg2 + 0x38);
    int last = func_02021980(arg1, arg2 + 0x40);
    int res = func_ov002_02076468(t0);
    int fx = func_02020400(t18 << 0x10, 0x168);
    func_ov014_020800a8(res, (unsigned short)r7, (unsigned short)t14, (unsigned short)r6,
                        (unsigned char)(unsigned short)(r6 >> 0x10), &buf[0], (short)fx, last);
    return 1;
}
