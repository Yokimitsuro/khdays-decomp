extern int func_02021980(void *a, int b);
extern int func_02021994(void *a, int b);
extern int func_02020400(int a, int b);
extern int func_ov002_0207679c(unsigned char a, unsigned short b);
extern void func_ov017_020804a4(int a, void *b, int c);

int func_ov017_02080bcc(void *arg1, int arg2) {
    int buf[3];
    int r6 = func_02021980(arg1, arg2);
    int r7 = func_02021980(arg1, arg2 + 8);
    buf[0] = func_02021994(arg1, arg2 + 0x10);
    buf[1] = func_02021994(arg1, arg2 + 0x18);
    buf[2] = func_02021994(arg1, arg2 + 0x20);
    unsigned short v = (unsigned short)func_02020400(func_02021980(arg1, arg2 + 0x28) << 0x10, 0x168);
    int res = func_ov002_0207679c((unsigned char)r6, (unsigned short)r7);
    func_ov017_020804a4(res, buf, (short)v);
    return 1;
}
