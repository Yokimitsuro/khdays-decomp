extern int func_0203c640();

struct Sub { char pad[0xad]; unsigned char flag; };
struct Mid { char pad0[4]; struct Sub *sub; };
struct Obj { char pad0[4]; struct Mid *mid; };

int func_ov164_020d2c54(struct Obj *obj) {
    if (obj->mid->sub->flag == 0) {
        return func_0203c640();
    }
    return (int)obj;
}
