extern int func_02021980(void *a, int b);
extern int func_02021994(void *a, int b);
extern int func_02020400(int a, int b);
extern int func_ov002_02076468(int a);
extern void func_ov017_020809d8(int a, unsigned short b, unsigned short c, void *d,
                                 int e, unsigned short f, int g, unsigned short h, int i, int j);

int func_ov017_02080d0c(void *arg1, int arg2) {
    int a = func_02021980(arg1, arg2 + 0x28);
    int buf[3];
    buf[0] = func_02021994(arg1, arg2 + 0x30);
    buf[1] = func_02021994(arg1, arg2 + 0x38);
    buf[2] = func_02021994(arg1, arg2 + 0x40);
    unsigned int r7 = *(unsigned int *)((char *)arg2 + 0x1c);
    unsigned int r6 = *(unsigned int *)((char *)arg2 + 0x24);
    int t = func_02021980(arg1, arg2 + 0x48);
    unsigned short fxh = (unsigned short)func_02020400(t << 0x10, 0x168);
    int res = func_ov002_02076468(func_02021980(arg1, arg2));
    int c = func_02021980(arg1, arg2 + 8);
    int d = func_02021980(arg1, arg2 + 0x10);
    func_ov017_020809d8(res, (unsigned short)c, (unsigned short)d, &buf[0],
                        (short)fxh, (unsigned short)r7, (unsigned char)(unsigned short)(r7 >> 0x10),
                        (unsigned short)r6, (unsigned char)(unsigned short)(r6 >> 0x10),
                        (short)a);
    return 1;
}
