extern unsigned short func_02020a9c(void);
extern int func_01fffde0(int arg0);
unsigned int func_ov022_020886f8(int arg0) {
    int p;
    if (func_02020a9c() == 0x2a) return 0;
    p = func_01fffde0(arg0);
    if (p == 0) return 0;
    return *(unsigned int *)p & 0x10000;
}
