extern void NNS_FndInitList(void *list, unsigned int offset);
extern void *func_0201bb6c(void *p);

int func_0201bb38(int *p, int arg1)
{
    NNS_FndInitList(p + 1, 0xc);
    p[0] = arg1;
    return func_0201bb6c(p) ? 1 : 0;
}
