struct Element {
    char data[16];
};

struct Container {
    unsigned short count;
    struct Element *base;
};

struct Element *func_02011840(struct Container *c, unsigned int index)
{
    if (c->count > index)
        return c->base + index;
    return 0;
}
