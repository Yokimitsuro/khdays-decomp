extern int func_0203c634();

struct Sub {
    char _pad[0x60];
    unsigned short flags;       /* 0x60 */
    char _pad2[0x1c7 - 0x62];
    signed char field_1c7;      /* 0x1c7 */
    signed char _pad3;          /* 0x1c8 */
    signed char field_1c9;      /* 0x1c9 */
};

struct Obj {
    char _pad0[4];
    struct Sub **pp;            /* 0x04 */
    char _pad1[0x20 - 8];
    signed char field_20;      /* 0x20 */
};

void func_ov274_020d1500(struct Obj *this) {
    struct Sub *s = *this->pp;
    if ((unsigned)(s->flags << 24) >> 24 & 1) {
        s->field_1c7 = s->field_1c9;
        func_0203c634(this, this->field_20, 0);
    }
}
