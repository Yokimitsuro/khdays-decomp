typedef struct { int w[15]; } Basis;
typedef struct { int w[3]; } Src3;

typedef struct {
    unsigned char type : 4;
    unsigned char kind : 4;
    char pad0[3];
    Src3 a;
    char pad1[0x58 - 0x10];
    Basis b;
    Basis c;
} Obj;

extern void *func_0203d15c(unsigned int size);
extern void func_0203c960(void *o);

void *func_ov107_020c32b8(Basis *self)
{
    Obj *obj = (Obj *)func_0203d15c(0xd0);

    obj->type = 2;
    obj->kind |= 1;

    obj->b = *self;
    obj->c = *self;

    func_0203c960((char *)obj + 0x10);

    obj->a = *(Src3 *)self;

    return obj;
}
