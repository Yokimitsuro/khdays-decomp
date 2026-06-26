struct T { int a, b, c; };
struct S { int pad[18]; struct T t; };

void func_0202e5d8(struct S *d, struct T *s)
{
    d->t = *s;
}
