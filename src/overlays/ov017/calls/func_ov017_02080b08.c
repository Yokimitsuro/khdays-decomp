extern int func_02021980(void *a, int b);
extern int func_02021994(void *a, int b);
extern int func_02020400(int a, int b);
extern int func_ov002_02076468(int a);
extern void func_ov017_020803c4(int a, unsigned short b, unsigned short c, unsigned short d,
                                 int e, unsigned short f, int g, unsigned short h, void *i, int j);

int func_ov017_02080b08(void *arg1, int arg2) {
    int t0 = func_02021980(arg1, arg2);
    int t1 = func_02021980(arg1, arg2 + 8);
    int t2 = func_02021980(arg1, arg2 + 0x10);
    unsigned int r7 = *(unsigned int *)((char *)arg2 + 0x1c);
    unsigned int r6 = *(unsigned int *)((char *)arg2 + 0x24);
    int t3 = func_02021980(arg1, arg2 + 0x28);
    int buf[3];
    buf[0] = func_02021994(arg1, arg2 + 0x30);
    buf[1] = func_02021994(arg1, arg2 + 0x38);
    buf[2] = func_02021994(arg1, arg2 + 0x40);
    int t = func_02021980(arg1, arg2 + 0x48);
    unsigned short fxh = (unsigned short)func_02020400(t << 0x10, 0x168);
    int res = func_ov002_02076468(t0);
    func_ov017_020803c4(res, (unsigned short)t1, (unsigned short)t2, (unsigned short)r7,
                        (unsigned char)(unsigned short)(r7 >> 0x10),
                        (unsigned short)r6,
                        (unsigned char)(unsigned short)(r6 >> 0x10),
                        (unsigned short)t3, &buf[0], (short)fxh);
    return 1;
}
