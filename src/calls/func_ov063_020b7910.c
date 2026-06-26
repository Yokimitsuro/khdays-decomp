extern int func_ov022_020acf14();
extern int func_ov022_020ad114();
extern int func_ov022_020ad0c0();
extern int func_01ff8bc4();
extern int func_01ff8cb8();
extern int func_01ff8d18();
extern int func_0200526c();

struct Obj {
    char pad0[0x20];
    void *off20;
    char pad24[0x64 - 0x24];
    unsigned short off64;
    char pad66[0x664 - 0x66];
    int (*method)();
};

struct Outer {
    char pad0[0xdb4];
    struct Obj *obj;
};

void func_ov063_020b7910(struct Outer *outer, int sel)
{
    int local[3];
    struct Obj *obj = outer->obj;
    unsigned short *p;

    switch (sel) {
    case 0x22:
        obj->method(obj, 0x2f);
        return;
    case 0x23:
        break;
    default:
        return;
    }

    obj->method(obj, 0x30);
    func_ov022_020acf14(obj, 0x39000);
    obj->off64 = 0x1000;
    if (func_ov022_020ad114(obj) == 0) {
        return;
    }
    func_01ff8bc4(func_ov022_020ad0c0(obj), (char *)obj + 0x8c + 0x400, local);
    if (func_01ff8cb8(local) != 0) {
        func_01ff8d18(local, local);
    }
    {
        unsigned short v = (unsigned short)func_0200526c(-local[0], -local[2]);
        p = (unsigned short *)obj->off20;
        if (*(int *)p & 0x20) {
            return;
        }
        p[0x80 / 2] = (unsigned short)(v + 0x8000);
        p[4 / 2] |= 0x20;
    }
}
