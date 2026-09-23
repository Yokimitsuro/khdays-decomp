/* Strafe move of the ov200 enemy (the handler func_ov200_020cf228 dispatches on its d201). Without a
 * target sub-state 2 is requested. Otherwise the owner keeps aiming at the target (+0x94 matrix)
 * and moves sideways around it: the flattened gap between the two collision radii (floored at 0)
 * gives the approach factor FX_Inv(0x4000 - gap, 0x4000) clamped to +/-1.0; the +0xc velocity is
 * the forward vector scaled by -factor plus the side vector (the +0xa4 strafe sign crossed with the
 * direction to the target) scaled by 1 - |factor|, both at 0x280, and the owner sinks at 0x180.
 * When the +0x80 timer has run out it is re-rolled in [+0x224, +0x228] after one discarded d101
 * and a sub-state is requested: 6 when all three +0x390 parts are clear, 7 when the last two are,
 * else 5 (2 instead of 6/7 while +0x1c4 bit 2 is set). Otherwise the chooser takes over again once
 * the +0x13c attack window drops below 2.0. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int obj, int kind);
extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_0203cd7c(int *dst, const Vec3 *a, const Vec3 *b, const void *c);
extern void func_0202ea48(int *dst, const int *src);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *dst);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern int FX_Inv(int num, int den);
extern void func_0202f384(Vec3 *dst, const int *a, const void *b);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *src, Vec3 *dst);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, int *out);
extern int func_02023eb4();
extern int func_ov200_020d055c(int slot);
extern void func_ov200_020cf228(void);
extern char data_02042264[];
extern char data_02042258[];

static inline void VEC_Set(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov200_020cf508(int self)
{
    int target;
    int *owner;
    int *ctx;
    int tgt;
    int *own2;
    int gap;
    int fac;
    int base;
    int span;
    int mtx[9];
    Vec3 toTarget;
    Vec3 up;
    Vec3 side;
    Vec3 dir;
    Vec3 fwd;

    ctx = *(int **)(self + 4);
    owner = (int *)ctx[0];
    ctx[2] = func_ov107_020cab14((int)owner, 0);
    target = ctx[2];
    if (target == 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    func_0203cd7c(mtx, (const Vec3 *)(target + 0x74), (const Vec3 *)ctx[0x13], data_02042264);
    func_0202ea48(&ctx[0x25], mtx);
    VEC_Subtract((const Vec3 *)ctx[0x13], (const Vec3 *)(target + 0x74), &toTarget);
    toTarget.y = 0;
    tgt = ctx[2];
    own2 = (int *)ctx[0];
    gap = func_01ff8d18(&toTarget, &toTarget);
    gap = (gap - *(int *)(tgt + 0x80)) - own2[0x20];
    if (gap < 0) {
        gap = 0;
    }
    fac = FX_Inv(0x4000 - gap, 0x4000);
    if (fac < -0x1000) {
        fac = -0x1000;
    }
    if (fac > 0x1000) {
        fac = 0x1000;
    }
    func_0202f384(&fwd, &ctx[0x25], data_02042258);
    VEC_Set(&up, 0, ctx[0x29] << 12, 0);
    VEC_CrossProduct(&up, &toTarget, &side);
    func_01ffa724(0x1000 - (fac < 0 ? -fac : fac), &side, &side);
    func_01ffa724(-fac, &fwd, &dir);
    func_01ffa724(0x280, &side, &side);
    func_01ffa724(0x280, &dir, &dir);
    VEC_Add(&side, &dir, &ctx[3]);
    ctx[4] = -0x180;

    if (ctx[0x20] <= 0) {
        func_02023eb4(0x65);
        base = *(int *)(ctx[0] + 0x224);
        span = *(int *)(ctx[0] + 0x228) - base;
        if (span < 0) {
            span = -span;
        }
        ctx[0x20] = base + func_02023eb4(span + 1);

        if (func_ov200_020d055c(*(int *)(ctx[0] + 0x390))
            && func_ov200_020d055c(*(int *)(ctx[0] + 0x394))
            && func_ov200_020d055c(*(int *)(ctx[0] + 0x398))) {
            *(signed char *)(ctx[0] + 0x1c7) = (*(unsigned char *)(ctx[0] + 0x1c4) & 4) ? 2 : 6;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }
        if (func_ov200_020d055c(*(int *)(ctx[0] + 0x394))
            && func_ov200_020d055c(*(int *)(ctx[0] + 0x398))) {
            *(signed char *)(ctx[0] + 0x1c7) = (*(unsigned char *)(ctx[0] + 0x1c4) & 4) ? 2 : 7;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }
        *(signed char *)(ctx[0] + 0x1c7) = 5;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if (owner[0x4f] >= 0x2000) {
        return;
    }
    func_0203c634(self, *(signed char *)(self + 0x20), func_ov200_020cf228);
}
