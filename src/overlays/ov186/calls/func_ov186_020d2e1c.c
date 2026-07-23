/* func_ov186_020d2e1c -- AI state: re-aim and re-arm the strafe step.
 *
 * The Q12 scale of the step (w38 * 0x6488, rounded with +0x800) is brought back down with a
 * 64-bit LOGICAL SHIFT, not a division: `/ 4096` on a signed long long makes mwcc call the
 * 64-bit divide helper, while `(unsigned long long)x >> 12` is the ROM's inline
 * `lsr r2,r2,#0xc ; orr r2,r2,r3,lsl #20`. Worth 12 bytes and three instructions.
 * Byte-identical twin of func_ov117_020cd594. */
extern int func_0202f384();
extern int func_01ffa724();
extern int func_0202f188();
extern int func_0203c9d0();
extern int func_02023eb4();
extern int func_0203c634();

extern int data_020420f8;
extern int data_02042258;
extern int data_02042270;

struct Inner {
    char pad0[0x1c7];
    unsigned char b1c7;        /* 0x1c7 */
    char pad1c8[0x224 - 0x1c8];
    int w224;                  /* 0x224 */
    int w228;                  /* 0x228 */
    char pad22c[0x384 - 0x22c];
    int w384;                  /* 0x384 */
};

struct Sub {
    struct Inner *inner;       /* 0x00 */
    char pad4[0x2c - 0x4];
    int w2c;                   /* 0x2c */
};

struct Mid {
    struct Inner *inner;       /* 0x00 */
    char pad4[8 - 4];
    char buf8[0x2c - 8];       /* 0x08 */
    char buf2c[0x38 - 0x2c];   /* 0x2c */
    int w38;                   /* 0x38 */
    char pad3c[0x40 - 0x3c];
    int w40;                   /* 0x40 */
};

struct Obj {
    struct Sub *sub;           /* 0x00 */
    struct Mid *mid;           /* 0x04 */
    char pad8[0x20 - 8];
    signed char b20;           /* 0x20 */
};

void func_ov186_020d2e1c(struct Obj *o)
{
    struct Mid *m;
    char local[16];

    m = o->mid;

    func_0202f384(m->buf2c, m->buf8, &data_02042258);
    func_01ffa724(0x100, m->buf2c, m->buf2c);

    func_0202f188(local, &data_02042270,
                  (int)((unsigned long long)((long long)m->w38 * 0x6488 + 0x800) >> 12));

    m->w38 = m->w38 + o->sub->w2c;
    func_0203c9d0(m->inner->w384 + 4, local);

    if (m->w38 < 0x1000)
        return;

    {
        int lo = m->inner->w224;
        int hi = m->inner->w228;
        int d = hi - lo;
        if (d < 0) d = -d;
        m->w40 = lo + func_02023eb4(d + 1);
    }

    func_0203c9d0(m->inner->w384 + 4, &data_020420f8);
    m->inner->b1c7 = 2;
    func_0203c634(o, o->b20, 0);
}
