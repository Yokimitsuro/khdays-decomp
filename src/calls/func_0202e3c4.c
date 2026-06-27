extern int func_0202e3f4(void *p);
extern void func_0202e1b0(void *p);
extern void func_0201f5ac(void *p);

void func_0202e3c4(void **p)
{
    if (func_0202e3f4(p) != 0) {
        func_0202e1b0(p[2]);
        func_0201f5ac(p[1]);
    }
    p[0] = 0;
}
