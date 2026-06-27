extern unsigned char *func_0201b578(int arg);
extern int func_0201ce18(int a0, unsigned char *a1, unsigned int a2, unsigned int a3,
                         int s0, int s1, int s2, int s3, int s4, int s5);

int func_0201cac0(int arg0, int arg1, int arg2)
{
    unsigned char *p = func_0201b578(arg1);
    if (p == 0) return 0;
    return func_0201ce18(arg0, p, p[6], p[5], arg1, arg2, 0, 0, 0, 0);
}
