extern int func_020170c8(void *p);
extern int func_0202e168(void *p, int a);
extern int func_0202e5cc(void *p, int a);

int func_0202e5e8(void **p)
{
    int v = func_020170c8(((void **)p[1])[3]);
    func_0202e168(p[2], v);
    return func_0202e5cc(p, 0);
}
