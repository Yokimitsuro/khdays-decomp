struct S {
    unsigned short count;
    unsigned short flags;
    char *base;
};

char *func_02011858(struct S *p)
{
    if (p->flags & 1) {
        return p->base + p->count * 16;
    } else {
        return p->base + p->count * 8;
    }
}
