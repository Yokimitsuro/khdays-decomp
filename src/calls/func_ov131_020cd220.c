extern int func_ov107_020cab14();
extern int func_01ff8a7c();
extern int func_0203c634();

struct S0 {
    char pad0[0x80];
    int field80;
    char pad84[0x1c7 - 0x84];
    char byte1c7;
    char pad1c8[0x2d8 - 0x1c8];
    int field2d8;
};

struct S1 {
    struct S0 *field0;
    int field4;
    int field8;
};

struct This {
    struct S0 *field0;
    struct S1 *field4;
    char pad8[0x20 - 8];
    signed char byte20;
};

int func_ov131_020cd220(struct This *this)
{
    struct S1 *p = this->field4;
    struct S0 *q;
    int result;
    int local;
    int t;

    result = func_ov107_020cab14(p->field0, &local);
    if ((p->field8 = result) == 0)
        return result;

    q = p->field0;
    t = func_01ff8a7c(local);
    t = t - (((struct S0 *)result)->field80 + q->field80);
    local = t;
    if (t > p->field0->field2d8)
        return p->field0->field2d8;

    p->field0->byte1c7 = 4;
    return func_0203c634(this, (signed char)this->byte20, 0);
}
