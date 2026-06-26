struct T { int a, b, c, d; };

struct S {
    struct T t;
    char pad[0x28 - 16];
    unsigned char flag;
};

int func_0203c9d0(struct S *dst, struct S *src)
{
    int v;
    dst->t = src->t;
    v = dst->flag & ~1;
    dst->flag = (unsigned char)v;
    return v;
}
