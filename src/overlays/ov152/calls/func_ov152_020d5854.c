extern int func_0203c634();

struct Sub {
    unsigned char *p00;
    char pad[0x44];
    unsigned char *p48;
};

struct Obj {
    char pad0[4];
    struct Sub *sub;
    char pad8[0x18];
    signed char c20;
};

void func_ov152_020d5854(struct Obj *o)
{
    struct Sub *s = o->sub;

    if (s->p48[0] != 0)
        return;

    s->p00[0x1c7] = 2;
    func_0203c634(o, o->c20, 0);
}
