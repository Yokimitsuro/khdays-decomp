struct Entry0201b6cc {
    char _0[0x10];
    unsigned int field_10;
    char _14[4];
};

struct Table0201b6cc {
    char _0[8];
    unsigned int count;
    char _c[0x84 - 0xc];
};

struct Root0201b6cc {
    char _0[0x84];
    struct Table0201b6cc *tbl;
};

extern struct Root0201b6cc *data_0204ad4c;

unsigned int func_0201b6cc(unsigned int idx)
{
    struct Table0201b6cc *tbl = data_0204ad4c->tbl;
    if (idx >= tbl->count) return 0;
    return ((struct Entry0201b6cc *)((char *)tbl + (idx << 4)))->field_10;
}
