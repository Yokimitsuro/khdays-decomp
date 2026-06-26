struct S { int *p; int pad; unsigned short n; };

int *func_02011538(struct S *s)
{
    return s->p + s->n * 4;
}
