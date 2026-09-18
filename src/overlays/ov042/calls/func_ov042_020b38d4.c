/*
 * Attack step: the per-frame body of the ov042 enemy's attack state.
 *
 * Marks bit 16 of both 64-bit flag words for the local player, samples the ground from a zero
 * vector (a grounded actor without bit 2 of +0x24 gets bit 46 and a zero +0x58) and adds the
 * horizontal step to +0x498. Once the +0x4cc timer reaches 0xf000 (0x1b000 in the rig's
 * alternate mode, +8) and the rig's shot latch (+4) is clear, it fires: the muzzle offset
 * (+0x11f, +0x1614, +0x10f6) is rotated by the actor's heading and added to the anchor at
 * +0x48c; in the alternate mode one homing shot (record flag +0x14 = 1) is fired and action 3/2
 * queued on the real actor, otherwise three shots at heading offsets 0, +0x1555, -0x1555 whose
 * +0x28 pattern index comes from a random row of the six permutations of {0,1,2}. Each shot's
 * direction is the unit z ray rotated by its heading, normalised and packed into the record's
 * three shorts before 02091324 spawns it. The latch is then raised. The state callback lands in
 * bit 1 of +0x694; a set bit 1 finishes the pose (bit 49, node reset unless bit 5, bit 1 of
 * +0x464 for the local player), clears the velocities, sets bit 2 and hands over to state 0
 * (after the slot callback) or 2.
 *
 * Spellings: the four tables are extern struct copies (`perm = data_...`) so the ldm/stm chains
 * come out; the unit ray is `extern const` and copied INSIDE the loop -- mwcc then hoists the
 * load into a stack temp (sp+4) exactly like the ROM, whereas a non-const extern is reloaded
 * from the pool each iteration and a pre-loop local lands before the loop guard. The slot
 * callback takes `(self, 0)`: the 0 is the zero already in r1 from the velocity clears.
 */
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct { int a[3]; } Angles;
typedef struct { int v[6][3]; } PermTable;
typedef struct {
    Vec3 pos;
    short f0c, f0e, f10, f12;
    int f14, f18, f1c, f20, f24, f28;
} Params;
typedef unsigned short u16;
typedef unsigned char u8;

extern int func_02030788(void);
extern int func_ov022_0209fe20(char *self, void *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern unsigned int func_020307f4(unsigned int n);
extern void MTX_RotY33_(Mtx33 *m, int s, int c);
extern void MTX_MultVec33(const Vec3 *v, const Mtx33 *m, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern void func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov022_02091324(char *self, Params *p);
extern void func_0202af1c(void *node);
extern void *func_ov022_020a35f4(char *self, int state);
extern char *data_ov042_020b4800;
extern Vec3 data_02041dc8;                  /* kVecZero */
extern Vec3 data_ov042_020b46a8;            /* muzzle offset */
extern Angles data_ov042_020b4690;          /* heading offsets of the three shots */
extern PermTable data_ov042_020b46f4;       /* the six permutations of {0,1,2} */
extern const Vec3 data_ov042_020b469c;            /* unit z ray */
extern short data_0203d210[];

void *func_ov042_020b38d4(char *self)
{
    PermTable perm;
    Vec3 sample;
    Vec3 muzzle;
    Mtx33 m;
    Params p;
    Angles angles;
    Vec3 v;
    Vec3 step;
    void *next = 0;
    char *rig = data_ov042_020b4800 + 0x2c + 0x2c00;
    int limit;
    int count;
    int rand;
    int i;
    int idx;
    int r;
    unsigned int *node;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    sample = data_02041dc8;
    func_ov022_0209fe20(self, &sample);
    if ((*(int *)(self + 0x24) & 4) == 0) {
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    step = sample;
    step.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &step, (Vec3 *)(self + 0x98 + 0x400));
    limit = *(int *)(rig + 8) != 0 ? 0x1b000 : 0xf000;
    if (*(int *)(self + 0x4cc) >= limit && *(int *)(rig + 4) == 0) {
        muzzle = data_ov042_020b46a8;
        angles = data_ov042_020b4690;
        perm = data_ov042_020b46f4;
        count = 1;
        p.f14 = 0;
        p.f1c = 1;
        p.f20 = 0;
        p.f18 = 0;
        p.f24 = 0;
        p.f28 = 0;
        p.f12 = 0xc00;
        if (*(int *)(rig + 8) != 0) {
            p.f14 = 1;
            if ((*(int *)self & 0x10000) == 0) {
                *(u8 *)(self + 0x47a) = 3;
                *(u8 *)(self + 0x47b) = 2;
            }
        } else {
            count = 3;
            rand = func_020307f4(6);
        }
        idx = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000) >> 4;
        MTX_RotY33_(&m, -data_0203d210[idx * 2], -data_0203d210[idx * 2 + 1]);
        MTX_MultVec33(&muzzle, &m, &p.pos);
        VEC_Add(&p.pos, (Vec3 *)(self + 0x8c + 0x400), &p.pos);
        for (i = 0; i < count; i++) {
            v = data_ov042_020b469c;
            if (*(int *)(rig + 8) != 0) {
                p.f28 = 0;
            } else {
                p.f28 = perm.v[rand][i];
            }
            idx = (u16)(angles.a[i] + (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000)) >> 4;
            MTX_RotY33_(&m, -data_0203d210[idx * 2], -data_0203d210[idx * 2 + 1]);
            MTX_MultVec33(&v, &m, &v);
            if (VEC_Mag(&v) != 0) {
                func_01ff8d18(&v, &v);
            }
            p.f0c = v.x;
            p.f0e = v.y;
            p.f10 = v.z;
            func_ov022_02091324(self, &p);
        }
        *(int *)(rig + 4) = 1;
    }
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (((Flags *)(self + 0x694))->b1) {
        *(unsigned long long *)self |= 0x2000000000000ULL;
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            func_0202af1c(node + 1);
        }
        if (func_02030788() == 0) {
            *(unsigned long long *)(self + 0x464) |= 2;
        }
    }
    if (((Flags *)(self + 0x694))->b1) {
        *(int *)(self + 0x4a0) = 0;
        *(int *)(self + 0x49c) = 0;
        *(int *)(self + 0x498) = 0;
        *(int *)(self + 0x6a0) = 0;
        *(int *)(self + 0x69c) = 0;
        *(int *)(self + 0x698) = 0;
        *(unsigned long long *)self |= 4;
        if ((*(int *)(self + 0x24) & 4) != 0) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0);
            next = func_ov022_020a35f4(self, 0);
        } else {
            next = func_ov022_020a35f4(self, 2);
        }
    }
    return next;
}
