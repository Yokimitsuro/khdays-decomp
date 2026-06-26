struct inner {
    char pad[0x5c];
    unsigned int flags;
};

struct mid {
    char pad[4];
    struct inner *a;
    struct inner *b;
    struct inner *c;
};

struct outer {
    char pad[4];
    struct mid *m;
};

void func_ov246_020d29fc(struct outer *r0)
{
    struct mid *m = r0->m;
    m->a->flags |= 2;
    m->b->flags |= 2;
    m->c->flags |= 2;
}
