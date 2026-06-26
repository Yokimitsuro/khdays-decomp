struct Inner {
    char pad[0x40];
    unsigned char field40;
};

struct Outer {
    struct Inner *volatile inner;
};

void func_0201a110(struct Outer *o, int val)
{
    if (o->inner) {
        o->inner->field40 = (unsigned char)val;
    }
}
