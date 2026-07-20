/* Initialise the ov301 object: install its seven handler pointers, seed the camera block
 * and the bounding box, then create the two pooled sub-objects.
 *
 * The box is built in a LOCAL and copied to self->box in one go, with each max derived from
 * the min FIELD just stored (`box.max.x = box.min.x + 0x1dd3`).  Deriving it from the local
 * that fed the min instead lets mwcc constant-fold to 0xee9 and materialise that cheaply
 * from another live constant, three instructions short.
 *
 * THE LAST LEVER, and it is one that was not in the catalogue: `register void *fn2c`.
 * The function was instruction-for-instruction identical to the ROM -- 92/92, all 16 relocs
 * matching by name and position -- for two sessions, differing only in which registers three
 * short-lived constants landed in.  The ROM spends r3, the register pushed purely for stack
 * alignment, on one of them; mwcc reached for callee-saved r6/r7 instead.  Twelve spellings
 * had been tried against that: every declaration order, the constants inlined, an explicit
 * local for 0x17, four different parameter counts, the box block moved, the box written
 * straight through a pointer.  None moved it, because none of them changes what mwcc is
 * WILLING to allocate -- only `register` does.
 *
 * Also load-bearing, and cheap to lose in a tidy-up: the fn2c pointer is held in that
 * register across the whole box construction and stored AFTER it, and the three mins are
 * assigned x, z, y in that order.
 *
 * With this, ov301 is 16/16.
 */
extern int func_ov301_020cc15c, func_ov301_020cc178, func_ov301_020cc240;
extern int WM_EndKeySharing_0x020cc1d8, WM_EndKeySharing_0x020cc1e4;
extern int func_ov301_020cc28c, func_ov301_020cc1f0;
extern int data_02041dc8[], data_02042264[];
extern int func_ov107_020c9440(int p, int a);
extern int func_0203b898(int r0);
extern void func_0203bfb4(int a, int b);
extern int *func_01fffca8(void *p, int sz, int n);
extern int func_ov107_020c3210(void *p);
extern int func_ov107_020c319c(void *p);

struct Vec3 { int x, y, z; };
struct Box  { struct Vec3 min, max; };
struct WorkBlock { int v[8]; };

struct Ov301Obj {
    char      pad_00[0x08];
    void     *fn08;          /* 0x08 */
    void     *fn0c;          /* 0x0c */
    char      pad_10[0x18];
    void     *fn28;          /* 0x28 */
    void     *fn2c;          /* 0x2c */
    void     *fn30;          /* 0x30 */
    char      pad_34[0x30];
    int       cam[4];        /* 0x64 */
    char      pad_74[0x28];
    int       p9c;           /* 0x9c */
    char      pad_a0[0xa4];
    char      pool144[0x6a]; /* 0x144 */
    unsigned short flags1ae; /* 0x1ae */
    char      pad_1b0[0x19];
    char      b1c9;          /* 0x1c9 */
    char      pad_1ca[0x06];
    void     *fn1d0;         /* 0x1d0 */
    char      pad_1d4[0x08];
    void     *fn1dc;         /* 0x1dc */
    char      pad_1e0[0x1c];
    struct Box box;          /* 0x1fc */
    char      pad_214[0x18];
    char      pool22c[0x158];/* 0x22c */
    int       p384;          /* 0x384 */
    int      *p388;          /* 0x388 */
    int       p38c;          /* 0x38c */
};

void func_ov301_020cbfc4(struct Ov301Obj *self)
{
    int minX;
    int minY;
    int minZ;
    register void *fn2c;

    struct WorkBlock work;
    struct Box box;
    int *slot;

    minX = 0xfffff116;
    minZ = 0xfffff7a8;
    minY = 0x17;

    self->fn08 = &func_ov301_020cc15c;
    self->fn0c = &func_ov301_020cc178;
    self->fn30 = &func_ov301_020cc240;
    self->fn28 = &WM_EndKeySharing_0x020cc1d8;

    fn2c = &WM_EndKeySharing_0x020cc1e4;

    box.min.x = minX;
    box.min.y = minY;
    box.min.z = minZ;

    box.max.x = box.min.x + 0x1dd3;
    box.max.y = box.min.y + 0x1c27;
    box.max.z = box.min.z + 0xd64;

    self->fn2c = fn2c;
    self->fn1d0 = &func_ov301_020cc28c;
    self->fn1dc = &func_ov301_020cc1f0;

    self->b1c9 = 2;

    self->cam[3] = 0x1900;
    self->cam[0] = 0;
    self->cam[1] = 0x400;
    self->cam[2] = 0;

    self->box = box;

    self->p384 = func_0203b898(func_ov107_020c9440((int)self, 0));
    func_0203bfb4(self->p9c, self->p384);

    self->flags1ae |= 0x10;

    *(struct Vec3 *)&work.v[0] = *(struct Vec3 *)data_02041dc8;
    *(struct Vec3 *)&work.v[3] = *(struct Vec3 *)data_02042264;
    work.v[6] = 0x4000;
    work.v[7] = 0x1900;

    self->p388 = func_01fffca8(&self->pool22c[0], 0x10, 0x64);
    *self->p388 = func_ov107_020c3210(&work);

    slot = func_01fffca8(&self->pool144[0], 4, 0x64);
    *slot = func_ov107_020c319c(&self->cam[0]);
    self->p38c = *slot;
}
