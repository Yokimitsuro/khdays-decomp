extern void func_ov022_0208acdc(int arg0, unsigned int *arg1, unsigned int arg2);
extern void func_ov022_0208a8bc(int arg0, int arg1, unsigned short *arg2, int arg3);
extern void func_ov022_0208a6b0(int arg0);

void func_ov022_0208b6c0(int arg0, unsigned int *arg1, unsigned int *arg2, unsigned int arg3) {
    int e = arg1[0x52];
    unsigned int v;
    *arg1 = 0;
    func_ov022_0208acdc(arg0, arg2, arg3);
    func_ov022_0208a8bc(arg0, (int)(arg1 + 0x49), (unsigned short *)(arg1 + 7), 2);
    v = *(unsigned int *)(e + 0x20);
    arg1[0x35] = v;
    arg1[0x34] = v;
    arg1[0x33] = v;
    func_ov022_0208a6b0(arg0);
    *(unsigned char *)(arg1 + 0x53) = 3;
}
