typedef struct Msg {
    char pad0[2];
    unsigned char field_2;
    unsigned char field_3;
} Msg;

typedef struct Res {
    char pad0[0x14];
    void (*field_14)(struct Res *self, int arg);
    char pad1[0x40 - 0x14 - 4];
    unsigned int field_40;
} Res;

typedef struct Ov107 {
    char pad[0xf8];
    unsigned int field_f8;
} Ov107;

extern unsigned int func_02030788(void);
extern void func_02031384(int cmd, Msg *msg, unsigned short val);
extern Res *func_ov107_020c9b68(unsigned char idx);
extern void func_ov107_020c2b20(int obj, int arg1);
extern void func_ov107_020c2b38(int obj, int arg1);

void func_ov107_020c27e8(Ov107 *self, Msg *msg, int arg2)
{
    unsigned char state = msg->field_2;

    if (state == 1) {
        if (func_02030788() != 0) {
            return;
        }
        msg->field_2 = 2;
        func_02031384(4, msg, (unsigned short)arg2);
    } else if (state == 2) {
        Res *res = func_ov107_020c9b68(msg->field_3);
        func_ov107_020c2b20((int)self, (int)res);
        res->field_40 |= 4;
        if (res->field_14) {
            res->field_14(res, 1);
        }
        self->field_f8 &= ~0xf;
    } else if (state == 3) {
        if (func_02030788() != 0) {
            return;
        }
        msg->field_2 = 4;
        func_02031384(4, msg, (unsigned short)arg2);
    } else if (state == 4) {
        Res *res = func_ov107_020c9b68(msg->field_3);
        func_ov107_020c2b38((int)self, (int)res);
        res->field_40 &= ~4;
        self->field_f8 &= ~0xf;
    }
}
