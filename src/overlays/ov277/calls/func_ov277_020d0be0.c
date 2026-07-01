extern int func_0203c634();

struct Sub {
    char pad0x1ae[0x1ae];
    unsigned short flags;
};

struct Obj {
    char pad0[4];
    struct Sub **psub;
    char pad8[0x20 - 8];
    signed char b20;
};

int func_ov277_020d0be0(struct Obj *r0)
{
    (*r0->psub)->flags |= 3;
    return func_0203c634(r0, r0->b20, 0);
}
