extern int func_0202a818(unsigned short *arg0, int arg1);
extern void func_ov022_0208a8bc(int arg0, int arg1, unsigned short *arg2, int arg3);

int func_ov022_0208cbf8(int arg0, int arg1) {
    int e = *(int *)(arg0 + *(int *)(arg0 + 0xc) * 4 + 0x18);
    if (func_0202a818((unsigned short *)(e + 8), arg1) != 0) {
        func_ov022_0208a8bc(arg0, *(int *)(arg0 + 0x54) + 4, (unsigned short *)(e + 8), 1);
        *(int *)(e + 0x11c) = 0;
        *(unsigned char *)(e + 0x118) = 2;
    }
    return 0;
}
