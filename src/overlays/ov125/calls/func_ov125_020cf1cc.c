/* Beam tick of the ov125 enemy (wind-down). The aim point is the midpoint of the two anchors
 * (+0x394 / +0x398 at +0x14); the +0x30 timer accumulates the owner's rate and, capped at 1.0
 * of 0x800, gives the fade t while the beam length stays 30.0. The state[2] sub-node faces the
 * aim point and state[1] takes the owner's +0xa0 basis turned by
 * data_02042258 (ed60 by data_02042240 + normalise) placed at the aim point. The beam (forward x
 * length) is cast against the world twice -- a swept sphere of 0x100 and a plain ray -- and the
 * nearer plane hit (squared plane distance of the aim point) clips it: the end point, its length
 * and the plane normal are kept, else the beam is normalised and the length is 30.0. state[1]
 * is scaled 2(1-t) x (length x 0.2) x 2(1-t); with a hit state[5] is placed 0x200 along the normal from
 * the end point and state[3] at the end point (both unflagged), otherwise both are flagged. In
 * the beam capsule (aim, end, length, 0x200) is swept over the actor list and every candidate
 * accepted along the unit vector from its closest point (0x400) gets the overlay's 14-byte
 * command with that point packed in and reaction 0x11b/6 at it. Once the timer passes 0x800
 * phase 0 is queued and the state ends.
 *
 * Codegen: nLen is declared first and the hit flags before the two result pointers -- that is
 * the ROM's callee-saved assignment (nLen r6, nBest r7, bHit1 r8, r1/bHit2 r5, owner/r2 sb). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int fx32;
typedef long long fx64;

typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { int q[4]; } Quat;
typedef struct { u16 h[7]; } Cmd14;

typedef struct {
    Vec3 p0;
    Vec3 dir;
    int nLength;
    int nRadius;
} Segment;

typedef struct {
    char pad00[0x14];
    short x, y, z;
    short pad1a;
    int d;
} PlaneS16;

typedef struct {
    Vec3 n;
    int d;
} Plane;

struct CollisionResult {
    int pad00;
    PlaneS16 *pPlane;
    int field08;
    int nAlong;
};

struct Ov125Phase { int cur : 4, next : 4; };

extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int FX_Inv(int num, int den);
extern void func_0203ca30(void *p, Vec3 *v);
extern void func_0202f384(Vec3 *out, void *pose, void *k);
extern void func_0202ed60(Quat *dst, void *src, Vec3 *m);
extern void func_0202f4a4(Quat *out, Quat *in);
extern void func_0203c9d0(void *pose, Quat *q);
extern struct CollisionResult *func_01fff8e8(void *collision, Vec3 *position, Vec3 *direction, int radius, void *ignore);
extern void func_01ffd144(int scale, Vec3 *in, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern struct CollisionResult *func_01fff920(void *collision, Vec3 *position, Vec3 *direction);
extern void func_0203ca50(void *placement, int x, int y, int z);
extern int func_ov107_020c8f44(int owner, Segment *query, int *results);
extern int func_02036304(Vec3 *point, Segment *seg, fx64 *outDist);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov107_020ca918(int ent, int owner, int aux, int mode, Vec3 *dir, int flag);
extern void func_ov107_020c5af8(int owner, int id, int a, Vec3 *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern int data_02042258;
extern int data_02042240;
extern Cmd14 data_ov125_020d03ea;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

void func_ov125_020cf1cc(int *node)
{
    int *state = (int *)node[1];
    Vec3 aim;
    Quat q;
    Vec3 fwd;
    Vec3 end;
    Vec3 beam;
    Vec3 normal;
    Vec3 sum;
    Plane plane;
    Vec3 side;
    Segment axis;
    int results[4];
    Vec3 hit;
    Vec3 dir2;
    Cmd14 cmd;
    Cmd14 tmpl;
    fx64 along;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int nHiY;
    int nHiZ;
    int nLen;
    int nBest;
    int bHit1;
    int bHit2;
    int t;
    struct CollisionResult *r1;
    struct CollisionResult *r2;
    char *collisionOwner = *(char **)(*state + 4);
    int nDist;
    int i;
    int n;

    VEC_Add((Vec3 *)(*(int *)(*state + 0x394) + 0x14), (Vec3 *)(*(int *)(*state + 0x398) + 0x14), &aim);
    func_01ffa724(0x800, &aim, &aim);
    state[0xc] += *(int *)(node[0] + 0x2c);
    t = FX_Inv(state[0xc], 0x800);
    if (t > 0x1000) t = 0x1000;
    nLen = 0x1e000;
    func_0203ca30((void *)(state[2] + 4), &aim);
    func_0202f384(&fwd, (char *)*state + 0xa0, &data_02042258);
    func_0202ed60(&q, &data_02042240, &fwd);
    func_0202f4a4(&q, &q);
    func_0203c9d0((void *)(state[1] + 4), &q);
    func_0203ca30((void *)(state[1] + 4), &aim);
    func_01ffa724(nLen, &fwd, &beam);
    r1 = func_01fff8e8(*(void **)(collisionOwner + 0x7c), &aim, &beam, 0x100, 0);
    if (r1 != 0 && r1->field08 == 0) {
        func_01ffd144(r1->nAlong, &beam, &end);
        VEC_Add(&aim, &end, &sum);
        nLen = func_01ff8d18(&end, &end);
        bHit1 = 1;
        normal.x = r1->pPlane->x;
        normal.y = r1->pPlane->y;
        normal.z = r1->pPlane->z;
        plane.n = normal;
        plane.d = r1->pPlane->d;
        nDist = VEC_DotProduct(&plane.n, &aim) - plane.d;
        nBest = FX_Mul(nDist, nDist);
    } else {
        bHit1 = 0;
    }
    r2 = func_01fff920(*(void **)(collisionOwner + 0x7c), &aim, &beam);
    if (r2 != 0 && r2->field08 == 0) {
        normal.x = r2->pPlane->x;
        normal.y = r2->pPlane->y;
        normal.z = r2->pPlane->z;
        plane.n = normal;
        plane.d = r2->pPlane->d;
        bHit2 = 0;
        if (bHit1 != 0) {
            nDist = VEC_DotProduct(&plane.n, &aim) - plane.d;
            bHit2 = 0;
            if (nBest < FX_Mul(nDist, nDist)) {
                goto scaled;
            }
        }
        {
            func_01ffd144(r2->nAlong, &beam, &end);
            VEC_Add(&aim, &end, &sum);
            nLen = func_01ff8d18(&end, &end);
            bHit2 = 1;
        }
    } else {
        func_01ff8d18(&beam, &end);
        nLen = 0x1e000;
        bHit2 = 0;
    }
scaled:
    func_0203ca50((void *)(state[1] + 4), (0x1000 - t) * 2, FX_Mul(nLen, 0x3333), (0x1000 - t) * 2);
    if (bHit2 != 0 || bHit1 != 0) {
        func_01ffa724(0x200, &normal, &side);
        VEC_Add(&side, &sum, &side);
        *(int *)(state[5] + 0x5c) &= ~2;
        func_0203ca30((void *)(state[5] + 4), &side);
        *(int *)(state[3] + 0x5c) &= ~2;
        func_0203ca30((void *)(state[3] + 4), &sum);
    } else {
        *(int *)(state[5] + 0x5c) |= 2;
        *(int *)(state[3] + 0x5c) |= 2;
    }
    if (*(int *)(*state + 0x50) == 1) {
    axis.p0 = aim;
    axis.dir = end;
    axis.nLength = nLen;
    axis.nRadius = 0x200;
    n = func_ov107_020c8f44(*state, &axis, results);
    i = 0;
    if (n > 0) {
        tmpl = data_ov125_020d03ea;
        do {
            func_02036304((Vec3 *)(results[i] + 0x74), &axis, &along);
            hit.x = (fx32)((along * axis.dir.x + 0x80000000LL) >> 32);
            hit.y = (fx32)((along * axis.dir.y + 0x80000000LL) >> 32);
            hit.z = (fx32)((along * axis.dir.z + 0x80000000LL) >> 32);
            VEC_Add(&axis.p0, &hit, &hit);
            VEC_Subtract((Vec3 *)(results[i] + 0x74), &hit, &dir2);
            func_01ff8d18(&dir2, &dir2);
            func_01ffa724(0x400, &dir2, &dir2);
            if (func_ov107_020ca918(results[i], *state, *state, 1, &dir2, 0) != 0) {
                cmd = tmpl;
                PACK(cmd, scratchX, *(Fx32 *)&hit.x, 5);
                PACK(cmd, scratchY, *(Fx32 *)&hit.y, 8);
                PACK(cmd, scratchZ, *(Fx32 *)&hit.z, 11);
                if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                    (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &cmd, 0xe);
                }
                func_ov107_020c5af8(*state, 0x11b, 6, &hit);
            }
        } while (++i < n);
    }
    }
    if (state[0xc] < 0x800) {
        return;
    }
    ((struct Ov125Phase *)(state + 0xd))->next = 0;
    func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
}
