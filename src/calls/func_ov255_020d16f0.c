extern int func_0203c640();

struct Sub { char pad[0xad]; unsigned char flag; };
struct Mid { char pad0[4]; struct Sub *sub; };
struct Obj { char pad0[4]; struct Mid *mid; };

int func_ov255_020d16f0(struct Obj *obj) {
    if (obj->mid->sub->flag == 0) {
        return func_0203c640();
    }
    return (int)obj;
}
