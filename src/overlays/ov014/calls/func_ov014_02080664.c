extern int func_02021980(void *a, int b);
extern int func_02021948(void *a, int b);
extern int func_02021994(void *a, int b);
extern int func_ov014_0207ffdc(unsigned short x, void *p);
extern void func_ov002_0207643c(int a, int b);

struct m14 {
    int a;
    int b;
    unsigned char c;
    unsigned char pad9;
    unsigned short d, e, f;
    int g;
    int h;
    int i;
    unsigned char j;
};

int func_ov014_02080664(void *arg1, int arg2) {
    struct m14 s;
    int r7 = func_02021980(arg1, arg2);
    int r6 = func_02021980(arg1, arg2 + 8);
    s.a = func_02021948(arg1, arg2 + 0x10);
    s.b = func_02021994(arg1, arg2 + 0x18);
    s.c = (unsigned char)func_02021980(arg1, arg2 + 0x20);
    s.d = (unsigned short)func_02021994(arg1, arg2 + 0x28);
    s.e = (unsigned short)func_02021994(arg1, arg2 + 0x30);
    s.f = (unsigned short)func_02021994(arg1, arg2 + 0x38);
    s.g = func_02021994(arg1, arg2 + 0x40);
    s.j = (unsigned char)func_02021980(arg1, arg2 + 0x48);
    s.h = func_02021994(arg1, arg2 + 0x50);
    s.i = func_02021994(arg1, arg2 + 0x58);
    {
        int r = func_ov014_0207ffdc((unsigned short)r6, &s);
        func_ov002_0207643c(r7, r);
    }
    return 1;
}
