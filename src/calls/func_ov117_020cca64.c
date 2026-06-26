struct Vec3 {
    int x;
    int y;
    int z;
};

extern int func_ov107_020c5c54();
extern int func_0203c634();

struct Blk {
    int a, b, c, d;
};

extern struct Blk data_020420f8;

struct C {
    char pad0[0x60];
    unsigned short flags;       /* 0x60 */
    char pad62[0x1c7 - 0x62];
    signed char field1c7;       /* 0x1c7 */
    signed char pad1c8;         /* 0x1c8 */
    signed char field1c9;       /* 0x1c9 */
};

struct B {
    struct C *field0;           /* 0x00 */
    char pad4[0x8 - 0x4];
    struct Blk field8;          /* 0x08 */
    struct Blk field18;         /* 0x18 */
    char pad28[0x44 - 0x28];
    struct Vec3 *field44;       /* 0x44 */
};

struct A {
    char pad0[0x4];
    struct B *field4;           /* 0x04 */
    char pad8[0x20 - 0x8];
    signed char field20;        /* 0x20 */
};

void func_ov117_020cca64(struct A *a) {
    struct B *b = a->field4;
    struct Vec3 local;

    if ((unsigned)(b->field0->flags << 24) >> 24 & 1) {
        b->field18 = data_020420f8;
        b->field8 = b->field18;

        local = *b->field44;
        local.y += 0xa00;
        func_ov107_020c5c54(b->field0, local);

        b->field0->field1c7 = b->field0->field1c9;
        func_0203c634(a, a->field20, 0);
    }
}
