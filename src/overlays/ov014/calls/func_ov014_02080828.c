extern int func_02021980(void *a, int b);
extern int func_02021994(void *a, int b);
extern int func_02020400(int a, int b);
extern int func_ov002_02076468(int a);
extern void func_ov014_020805cc(int a, unsigned short b, unsigned short c, unsigned short d,
                                 int e, void *f, int g);

int func_ov014_02080828(void *arg1, int arg2) {
    int t0 = func_02021980(arg1, arg2);
    int r7 = func_02021980(arg1, arg2 + 8);
    int t10 = func_02021980(arg1, arg2 + 0x10);
    unsigned int r6 = *(unsigned int *)((char *)arg2 + 0x1c);
    int buf[3];
    buf[0] = func_02021994(arg1, arg2 + 0x20);
    buf[1] = func_02021994(arg1, arg2 + 0x28);
    buf[2] = func_02021994(arg1, arg2 + 0x30);
    int t = func_02021980(arg1, arg2 + 0x38);
    int r5 = func_ov002_02076468(t0);
    int fx = func_02020400(t << 0x10, 0x168);
    func_ov014_020805cc(r5, (unsigned short)r7, (unsigned short)t10, (unsigned short)r6,
                        (unsigned char)(unsigned short)(r6 >> 0x10), &buf[0], (short)fx);
    return 1;
}
