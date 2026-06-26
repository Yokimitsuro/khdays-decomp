extern int func_ov107_020c5c54();
extern int func_ov002_0207298c();
extern int func_0203c634();

struct Vec3 {
    int x;
    int y;
    int z;
};

struct C {
    char pad0[0x60];
    unsigned short field60;
    char pad62[0xb0 - 0x62];
    struct Vec3 fieldB0;
    char padBC[0x1c7 - 0xbc];
    signed char field1c7;
    signed char pad1c8;
    signed char field1c9;
};

struct B {
    struct C *field0;
    char pad4[0x14 - 0x4];
    struct Vec3 field14;
    char pad20[0x88 - 0x20];
    int field88;
};

struct A {
    char pad0[0x4];
    struct B *field4;
    char pad8[0x20 - 0x8];
    signed char field20;
};

void func_ov115_020cd530(struct A *a)
{
    struct B *b = a->field4;
    struct C *c = b->field0;

    if ((unsigned)(c->field60 << 24) >> 24 & 1) {
        b->field14 = c->fieldB0;

        b->field14.y += 0x2000;

        b->field88 = (func_ov002_0207298c(func_ov107_020c5c54(b->field0)) == 8);

        b->field0->field1c7 = b->field0->field1c9;

        func_0203c634(a, a->field20, 0);
    }
}
