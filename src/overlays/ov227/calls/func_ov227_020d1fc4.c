extern int func_02023eb4();
extern int func_0203c634();

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

struct S2 {
    u8 pad0[0x60];
    u16 lo8 : 8;    /* 0x60 low byte */
    u16 hi8 : 8;    /* 0x60 high byte */
};

struct S0 {
    struct S2 *p0;  /* 0x00 */
    u8 *p4;         /* 0x04 */
    u8 pad8[0x68 - 8];
    int f68;        /* 0x68 */
    u8 pad6c[0x78 - 0x6c];
    int f78;        /* 0x78 */
};

struct This {
    u8 pad0[4];
    struct S0 *p4;  /* 0x04 */
    u8 pad8[0x20 - 8];
    s8 f20;         /* 0x20 */
};

void func_ov227_020d1fc4(struct This *this)
{
    struct S0 *s0 = this->p4;
    struct S2 *s2 = s0->p0;
    int diff;

    s2->hi8 = s2->hi8 & ~0xE;

    if (s0->p4[0xad] != 0)
        return;

    {
        int a = *(int *)((u8 *)s0->p0 + 0x224);
        int b = *(int *)((u8 *)s0->p0 + 0x228);
        diff = b - a;
        if (diff < 0) diff = -diff;
        s0->f68 = a + func_02023eb4(diff + 1);
    }
    s0->f78 = 1;
    *((u8 *)s0->p0 + 0x1c7) = 5;
    func_0203c634(this, (s8)this->f20, 0);
}
