extern int func_0203c634();

struct Inner {
    unsigned char *p0;
    unsigned char *p4;
};

struct Obj {
    int field0;
    struct Inner *field4;
    char pad8[0x18];
    signed char field20;
};

int func_ov119_020cda84(struct Obj *obj)
{
    struct Inner *inner = obj->field4;

    if (inner->p4[0xad] != 0)
        return (int)obj;

    inner->p0[0x1c7] = 7;
    return func_0203c634(obj, obj->field20, 0);
}
