extern int func_02021980(void *a, int b);
extern int func_ov002_02076468(int a);
extern void func_ov020_0207fcd4(int a, unsigned short b, unsigned short c, unsigned short d, int e);

int func_ov020_0207fa7c(void *arg1, int arg2) {
    int r7 = func_02021980(arg1, arg2);
    int r6 = func_02021980(arg1, arg2 + 8);
    int r4 = func_02021980(arg1, arg2 + 0x10);
    unsigned int r5 = *(unsigned int *)((char *)arg2 + 0x1c);
    int res = func_ov002_02076468(r7);
    func_ov020_0207fcd4(res, (unsigned short)r6, (unsigned short)r4, (unsigned short)r5,
                        (unsigned char)(unsigned short)(r5 >> 0x10));
    return 1;
}
