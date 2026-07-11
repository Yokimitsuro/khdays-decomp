extern int func_02021980(void *a, int b);
extern int func_02021948(void *a, int b);
extern int func_02021994(void *a, int b);
extern int func_ov017_020802d8(unsigned short x, void *p);
extern void func_ov002_0207643c(int a, int b);

struct m {
    int a, b, c, d;
    unsigned char e;
    unsigned char pad;
    unsigned short f, g, h;
};

int func_ov017_02080a6c(void *arg1, int arg2) {
    struct m s;
    int r7 = func_02021980(arg1, arg2);
    int r6 = func_02021980(arg1, arg2 + 8);
    s.a = func_02021948(arg1, arg2 + 0x10);
    s.b = func_02021948(arg1, arg2 + 0x18);
    s.c = func_02021948(arg1, arg2 + 0x20);
    s.d = func_02021994(arg1, arg2 + 0x28);
    s.e = (unsigned char)func_02021980(arg1, arg2 + 0x30);
    s.f = (unsigned short)func_02021994(arg1, arg2 + 0x38);
    s.g = (unsigned short)func_02021994(arg1, arg2 + 0x40);
    s.h = (unsigned short)func_02021994(arg1, arg2 + 0x48);
    {
        int r = func_ov017_020802d8((unsigned short)r6, &s);
        func_ov002_0207643c(r7, r);
    }
    return 1;
}
