extern int func_ov107_020c5af8();
extern int func_0203c634();

struct Inner2 {
    char _pad0[8];
    unsigned int bf8 : 8;      /* 0x08, bits [7:0] */
    unsigned int _bf8hi : 24;  /* 0x08, bits [31:8] */
};

struct Inner {
    char _pad0[0x60];
    unsigned short lo : 8;      /* 0x60, bits [7:0] */
    unsigned short hi : 8;      /* 0x60, bits [15:8] */
    char _pad1[0x1c7 - 0x62];
    unsigned char b1c7;         /* 0x1c7 */
    char _pad2[0x38c - 0x1c8];
    struct Inner2 *p38c;        /* 0x38c */
};

struct B {
    struct Inner *p0;          /* 0x00 */
    char _pad1[0x40 - 4];
    int f40;                   /* 0x40 */
};

struct A {
    char _pad0[4];
    struct B *f4;              /* 0x04 */
    char _pad1[0x20 - 8];
    signed char f20;           /* 0x20 */
};

void func_ov202_020cea88(struct A *this)
{
    struct B *b = this->f4;

    b->p0->hi &= ~1;
    b->p0->hi |= (unsigned short)0x86;
    b->p0->p38c->bf8 &= ~1u;

    func_ov107_020c5af8(b->p0, 0, 0x49, b->f40);

    b->p0->b1c7 = 0;
    func_0203c634(this, this->f20, 0);
}
