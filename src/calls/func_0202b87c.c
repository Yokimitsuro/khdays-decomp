extern int func_0202b168(int *p);

typedef struct {
    unsigned short field_00;
    unsigned short field_02;
    int field_04;
    int field_08;
    int field_0c;
    int field_10;
} Msg;

typedef struct {
    int field_00;
    char pad_04[0x10c];
    char sub_110[0x48];
    int field_158;
} Obj;

typedef struct {
    int field_00;
    int field_04;
    int field_08;
    int field_0c;
    int field_10;
} MsgSrc;

typedef struct {
    char pad_00[8];
    unsigned char field_08;
    char pad_09[3];
    Obj obj_0c;
} TopObj;

extern int func_0202b234(Obj *this_, Msg *msg);

void func_0202b87c(void *obj, int a, int b, void *c, int d) {
    TopObj *top = (TopObj *)obj;
    func_0202b168((int *)&top->obj_0c);
    if (c != 0) {
        MsgSrc *src = (MsgSrc *)c;
        Msg msg;
        msg.field_00 = (unsigned short)src->field_00;
        msg.field_02 = (unsigned short)a;
        msg.field_04 = src->field_04;
        msg.field_08 = src->field_08;
        msg.field_04 = src->field_04;
        msg.field_0c = src->field_0c;
        msg.field_10 = src->field_10;
        func_0202b234(&top->obj_0c, &msg);
        top->obj_0c.field_158 = b;
    }
    top->field_08 |= 1;
    if (d != 0) {
        top->field_08 |= 0x20;
    } else {
        top->field_08 &= ~0x20;
    }
}
