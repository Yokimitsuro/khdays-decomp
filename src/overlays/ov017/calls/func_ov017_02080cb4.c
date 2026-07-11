extern int func_02021948(void *a, int b);
extern int func_02021994(void *a, int b);
extern int func_02021980(void *a, int b);
extern int func_ov017_02080938(unsigned short x, void *p);
extern void func_ov002_0207643c(int a, int b);

struct m3 { int a, b; unsigned char c; };

int func_ov017_02080cb4(void *arg1, int arg2) {
    struct m3 s;
    s.a = func_02021948(arg1, arg2 + 0x10);
    s.b = func_02021994(arg1, arg2 + 0x18);
    s.c = (unsigned char)func_02021980(arg1, arg2 + 0x20);
    {
        int r6 = func_02021980(arg1, arg2);
        int v = func_02021980(arg1, arg2 + 8);
        int r = func_ov017_02080938((unsigned short)v, &s);
        func_ov002_0207643c(r6, r);
    }
    return 1;
}
