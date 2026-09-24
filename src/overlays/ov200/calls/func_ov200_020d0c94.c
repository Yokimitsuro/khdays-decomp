/* Ov200_TickBeam -- per-frame update of the ov200 enemy's beam (x3 with ov201 / ov271, which only
 * change the hit effect id). The emitter sits halfway between the +0x48 and +0x4c points, faces the
 * owner's +0xa0 heading and casts `len` ahead: a swept sphere (radius 1/16) and a plain ray against
 * the world, keeping whichever surface is nearer (squared plane distance) as the beam end and the
 * shortened length (7.5 when nothing is hit). The beam model is scaled to 3 x the width (1.5, or
 * 1.0 once charged) by a tenth of the length. In owner phase 1 with bTest the beam is a capsule
 * query (radius 1.0, or 0.1875 charged): every entity in front of the owner not already hit gets a
 * kind hit pushed away from the beam axis (plus 0.5 up), with hit effect 0x157 at the axis point;
 * a charged beam then stops and hands the node over. Uncharged, every other ready actor of the
 * world's +0x80 list whose shapes the capsule crosses receives a 4 packet (straight up) once per
 * activation (64-bit +0x3c mask). The end point shows the impact and glow models (hidden when
 * nothing was hit). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef long long fx64;
typedef unsigned long long u64;

typedef struct VecFx32 { int x, y, z; } VecFx32;
typedef struct Quat { int x, y, z, w; } Quat;
typedef struct Segment { VecFx32 p0; VecFx32 dir; int scale; } Segment;
typedef struct BeamQuery { VecFx32 p0; VecFx32 dir; int nLength; int nRadius; } BeamQuery;
typedef struct Plane { VecFx32 n; int d; } Plane;
typedef struct CollPlane { char pad00[0x14]; short x, y, z; short pad1a; int d; } CollPlane;
struct CollisionHit { int pad00; CollPlane *pPlane; int nBlocked; int nAlong; };
struct hw60 { unsigned short lo : 8, hi : 8; };
struct w8 { unsigned int lo : 8, rest : 24; };

struct HitPacket {
    u32 flagsLo : 16;
    u32 flagsHi : 16;
    VecFx32 normal;
    int field_10 : 16;
    int field_12 : 16;
    int field_14 : 16;
    int field_16 : 16;
    void *field_18;
    signed char field_1c;
    u8 pad01d[3];
    int field_20;
    u32 flags24Lo : 16;
    u32 flags24Hi : 16;
    int field_28;
};

typedef struct Ov200BeamState {
    int pOwner;           /* +0x00 */
    char *pBeam;          /* +0x04: beam model (srt at +4) */
    char *pEmitter;       /* +0x08 */
    char *pImpact;        /* +0x0c */
    char *pGlow;          /* +0x10 */
    int bCharged;         /* +0x14 */
    char pad18[0x30 - 0x18];
    int *pRing;           /* +0x30 */
    int pad34;
    int nFlags38;         /* +0x38 */
    u32 aHitMask[2];      /* +0x3c: actors already hit (64-bit) */
    u8 nHitKinds;         /* +0x44 */
    char pad45[3];
    VecFx32 *pFrom;       /* +0x48 */
    VecFx32 *pTo;         /* +0x4c */
} Ov200BeamState;

extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_01ffa724(int scale, const VecFx32 *in, VecFx32 *out);
extern void func_0203ca30(void *srt, const VecFx32 *trans);
extern void func_0202f384(VecFx32 *out, void *rot, const VecFx32 *in);
extern void func_0202ed60(Quat *out, const VecFx32 *from, const VecFx32 *to);
extern void func_0202f4a4(Quat *in, Quat *out);
extern void func_0203c9d0(void *srt, Quat *q);
extern struct CollisionHit *func_01fff8e8(void *coll, VecFx32 *origin, VecFx32 *dir, int radius, void *ignore);
extern struct CollisionHit *func_01fff920(void *coll, VecFx32 *origin, VecFx32 *dir);
extern void func_01ffd144(int scale, VecFx32 *in, VecFx32 *out);
extern int func_01ff8d18(VecFx32 *in, VecFx32 *out);
extern void func_ov200_020d1688(int *ring, VecFx32 *pos, VecFx32 *normal);
extern void func_0203ca50(void *srt, int x, int y, int z);
extern int func_ov107_020c8f44(int owner, BeamQuery *query, int *hits);
extern int func_02036304(void *point, Segment *seg, fx64 *t);
extern int func_ov107_020ca918(int hit, int owner, int item, u8 kind, VecFx32 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, VecFx32 at, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, VecFx32 *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern int *func_01fffd70(int list);
extern int *func_01fffd8c(int list);
extern int func_ov107_020c38ac(void *shape, BeamQuery *query, int flags);
extern int func_ov107_020c5cfc(int other, int source, struct HitPacket *packet);
extern const VecFx32 data_02042258;
extern const VecFx32 data_02042240;
extern const short data_0203d210[];
extern const VecFx32 data_02041dc8;

static inline int ANG2IDX(int a)
{
    return (unsigned short)(((long long)a * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
}

/* XZ facing of an actor from its +0x3ac yaw. */
static inline void FacingXZ(VecFx32 *out, int actor)
{
    int idx = ANG2IDX(*(int *)(actor + 0x3ac)) * 2;

    out->y = 0;
    out->x = data_0203d210[idx];
    out->z = data_0203d210[idx + 1];
}

/* Closest point of the segment axis to `point`, into `out`. */
static inline void AxisPoint(void *point, Segment *seg, fx64 *t, VecFx32 *out)
{
    func_02036304(point, seg, t);
    out->x = (int)((*t * seg->dir.x + 0x80000000LL) >> 32);
    out->y = (int)((*t * seg->dir.y + 0x80000000LL) >> 32);
    out->z = (int)((*t * seg->dir.z + 0x80000000LL) >> 32);
    VEC_Add(&seg->p0, out, out);
}

void func_ov200_020d0c94(int *node, int len, int bTest)
{
    VecFx32 pos;
    Quat quat;
    VecFx32 fwd;
    VecFx32 d;
    VecFx32 ray;
    VecFx32 normal;
    VecFx32 hitPos;
    Plane plane;
    BeamQuery query;
    Segment seg;
    VecFx32 tmp;
    int hits[4];
    VecFx32 closest;
    VecFx32 push;
    VecFx32 dirH;
    VecFx32 toHit;
    VecFx32 closest2;
    fx64 t;
    fx64 t2;
    u8 hitKinds = 0;
    int bRay;
    int bSphere;
    int n;
    Ov200BeamState *state = (Ov200BeamState *)node[1];
    int world = *(int *)(state->pOwner + 4);
    int width;
    int dist2;
    struct CollisionHit *hit;
    int i;

    width = state->bCharged == 0 ? 0x1800 : 0x1000;
    VEC_Add(state->pFrom, state->pTo, &pos);
    func_01ffa724(0x800, &pos, &pos);
    func_0203ca30(state->pEmitter + 4, &pos);
    func_0202f384(&fwd, (void *)(state->pOwner + 0xa0), &data_02042258);
    func_0202ed60(&quat, &data_02042240, &fwd);
    func_0202f4a4(&quat, &quat);
    func_0203c9d0(state->pBeam + 4, &quat);
    func_0203ca30(state->pBeam + 4, &pos);
    func_01ffa724(len, &fwd, &ray);
    hit = func_01fff8e8(*(void **)(world + 0x7c), &pos, &ray, 0x100, 0);
    if (hit != 0 && hit->nBlocked == 0) {
        func_01ffd144(hit->nAlong, &ray, &d);
        VEC_Add(&pos, &d, &hitPos);
        len = func_01ff8d18(&d, &d);
        bSphere = 1;
        normal.x = hit->pPlane->x;
        normal.y = hit->pPlane->y;
        normal.z = hit->pPlane->z;
        func_ov200_020d1688(state->pRing, &hitPos, &normal);
        plane.n = normal;
        plane.d = hit->pPlane->d;
        {
            int dist = VEC_DotProduct(&plane.n, &pos) - plane.d;
            dist2 = (int)(((long long)dist * dist + 0x800) >> 12);
        }
    } else {
        bSphere = 0;
    }
    hit = func_01fff920(*(void **)(world + 0x7c), &pos, &ray);
    if (hit != 0 && hit->nBlocked == 0) {
        normal.x = hit->pPlane->x;
        normal.y = hit->pPlane->y;
        normal.z = hit->pPlane->z;
        plane.n = normal;
        plane.d = hit->pPlane->d;
        if (bSphere) {
            int dist = VEC_DotProduct(&plane.n, &pos) - plane.d;
            bRay = 0;
            if (dist2 < (int)(((long long)dist * dist + 0x800) >> 12)) {
                goto scaled;
            }
        }
        func_01ffd144(hit->nAlong, &ray, &d);
        VEC_Add(&pos, &d, &hitPos);
        len = func_01ff8d18(&d, &d);
        bRay = 1;
        func_ov200_020d1688(state->pRing, &hitPos, &normal);
    } else {
        func_01ff8d18(&ray, &d);
        len = 0x1e000;
        bRay = 0;
    }
scaled:
    func_0203ca50(state->pBeam + 4, width * 3, (int)(((long long)len * 0x1999 + 0x800) >> 12), width * 3);
    if (*(int *)(state->pOwner + 0x50) == 1 && bTest != 0) {
        query.p0 = pos;
        query.dir = d;
        if (bRay == 0 && bSphere == 0) {
            query.nLength = len;
        } else {
            VEC_Subtract(&hitPos, &pos, &tmp);
            query.nLength = func_01ff8d18(&tmp, &tmp);
        }
        query.nRadius = state->bCharged == 0 ? 0x1000 : 0x300;
        n = func_ov107_020c8f44(state->pOwner, &query, hits);
        for (i = 0; i < n; i++) {
            u8 bit = (u8)(1 << *(u16 *)(hits[i] + 2));
            int front = 0;

            FacingXZ(&dirH, state->pOwner);
            VEC_Subtract((VecFx32 *)(hits[i] + 0x74), (VecFx32 *)(state->pOwner + 0x74), &toHit);
            func_01ff8d18(&toHit, &toHit);
            if (VEC_DotProduct(&dirH, &toHit) >= 0) {
                front = 1;
            }
            if (front && (state->nHitKinds & bit) == 0) {
                AxisPoint((void *)(hits[i] + 0x74), &seg, &t, &closest);
                VEC_Subtract((VecFx32 *)(hits[i] + 0x74), &closest, &push);
                func_01ff8d18(&push, &push);
                func_01ffa724(0x800, &push, &push);
                push.y = 0x800;
                if (func_ov107_020ca918(hits[i], state->pOwner, state->pOwner, state->bCharged == 0, &push, 0) != 0) {
                    func_ov107_020c0b90(state->pOwner, 0, closest, 0);
                    func_ov107_020c5af8(state->pOwner, 0x157, 6, &closest);
                    if (state->bCharged != 0) {
                        state->nFlags38 = (state->nFlags38 & ~0xf0) | 0x20;
                        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                        return;
                    }
                    hitKinds |= bit;
                }
            }
        }
        state->nHitKinds |= hitKinds;
        if (state->bCharged == 0) {
            int *entry = func_01fffd70(world + 0x80);
            int other = entry == 0 ? 0 : *entry;

            if (other != 0) {
                do {
                    if (other != state->pOwner && (((struct hw60 *)(other + 0x60))->lo & 1) != 0
                        && (*(u16 *)(other + 0x1ac) & 1) == 0 && (*(u16 *)(other + 0x1ac) & 2) == 0
                        && (*(u16 *)(other + 0x1ac) & 4) == 0
                        && ((*(u64 *)state->aHitMask >> *(u16 *)(other + 2)) & 1) == 0) {
                        int *shape;

                        for (shape = func_01fffd70(other + 0x22c); shape != 0; shape = func_01fffd8c(other + 0x22c)) {
                            if ((((struct w8 *)(shape + 2))->lo & 1) != 0 && func_ov107_020c38ac((void *)shape[0], &query, 0) != 0) {
                                struct HitPacket packet = {0};

                                packet.flagsLo = 4;
                                packet.normal = data_02041dc8;
                                packet.normal.y = 0x1000;
                                packet.field_10 = *(u16 *)(state->pOwner + 0x296);
                                packet.field_14 = *(int *)(state->pOwner + 0x258);
                                packet.field_18 = shape;
                                AxisPoint((void *)(shape[0] + 4), &seg, &t2, &closest2);
                                if ((((struct w8 *)(shape + 2))->lo & 1) != 0 && func_ov107_020c5cfc(other, 0, &packet) != 0) {
                                    func_ov107_020c0b90(state->pOwner, 0, closest2, 0);
                                    func_ov107_020c5af8(state->pOwner, 0x157, 6, &closest2);
                                    *(u64 *)state->aHitMask |= (u64)1 << *(u16 *)(other + 2);
                                }
                                break;
                            }
                        }
                    }
                    entry = func_01fffd8c(world + 0x80);
                    other = entry == 0 ? 0 : *entry;
                } while (other != 0);
            }
        }
    }
    if (bRay != 0 || bSphere != 0) {
        VecFx32 tip;

        func_01ffa724(0x200, &normal, &tip);
        VEC_Add(&tip, &hitPos, &tip);
        *(int *)(state->pGlow + 0x5c) &= ~2;
        func_0203ca30(state->pGlow + 4, &tip);
        *(int *)(state->pImpact + 0x5c) &= ~2;
        func_0203ca30(state->pImpact + 4, &hitPos);
    } else {
        *(int *)(state->pGlow + 0x5c) |= 2;
        *(int *)(state->pImpact + 0x5c) |= 2;
    }
}
