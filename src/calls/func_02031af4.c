extern unsigned int func_02011840(unsigned int a, unsigned int b);
extern void func_02012444(void *p, unsigned int v, void *q);

void func_02031af4(void *p, unsigned int a, void *q, int b)
{
    unsigned int v;
    if (b < 0) return;
    v = func_02011840(a, (unsigned int)(unsigned short)b);
    func_02012444(p, v, q);
}
