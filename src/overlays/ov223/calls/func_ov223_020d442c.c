/* Strike sweep of the ov223 enemy's charge. With a segment the entities come from the +0x38c
 * item's segment query (ov107 c8f44) and the segment is cast against the world twice -- a
 * swept sphere of its radius and a plain ray -- and the first clean hit builds a 32-byte
 * kind-5 command-2 message (id, the pose facing the plane normal from data_02042264, the hit
 * point packed as 24-bit values) for the owner's +0x24 hook; with a sphere they come from the
 * sphere query (ov107 c8eb8). Every entity whose kind bit is clear in the +0x4c mask is
 * pushed along the flattened unit direction from the owner's +0x74 with the +0x48 variant as
 * the kind; on acceptance the entity's +0x74 (or the sphere's point) goes to ov223 43e4,
 * reaction 0x149 mode 8 fires at the +8 point and the bit is set. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { int q[4]; } Quat;
typedef struct { Vec3 pos; int nRadius; } Sphere;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;

typedef struct {
    u16 id;
    u8 kind;
    u8 cmd;
    Quat pose;
    u8 pos[9];
    u8 pad[3];
} HitMsg;

typedef struct { char pad00[0x14]; short x, y, z; } PlaneS16;
struct CollisionHit { int pad00; PlaneS16 *pPlane; int nBlocked; int nAlong; };

struct Ov223Hit { char pad000[2]; u16 nKind; char pad004[0x70]; Vec3 vOrigin74; };

#define PACK(msg, dead, src, at)                                              \
    (dead) = (src);                                                           \
    (msg).pos[at] = (u8)(((u32)(dead).value >> 0x10 & 0x7f)                   \
                         | ((u32)(dead).value >> 0x18 & 0x80));               \
    (msg).pos[(at) + 1] = (u8)((u32)(dead).value >> 8);                       \
    (msg).pos[(at) + 2] = (u8)(dead).value

extern int func_ov107_020c8f44(int item, Segment *query, struct Ov223Hit **results);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern struct CollisionHit *func_01fff8e8(void *collision, Vec3 *origin, Vec3 *dir, int radius, void *ignore);
extern void func_01ffd144(int scale, Vec3 *in, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern struct CollisionHit *func_01fff920(void *collision, Vec3 *origin, Vec3 *dir);
extern int func_ov107_020c8eb8(int item, Sphere *query, struct Ov223Hit **results);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(struct Ov223Hit *hit, int owner, int item, u8 kind, Vec3 *push, int z);
extern void func_ov223_020d43e4(int *state, Vec3 v);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern const Vec3 data_02042264;

void func_ov223_020d442c(int *node, Sphere *pSphere, Segment *pSeg)
{
    int *state = (int *)node[1];
    struct Ov223Hit *hits[4];
    Vec3 end;
    Vec3 normal;
    Vec3 beam;
    int n;
    int i;
    u8 bit;
    u16 *p;
    char *coll;
    struct CollisionHit *hit;

    if (pSeg != 0) {
        coll = *(char **)(*state + 4);
        {
        HitMsg msg = {0};
        p = (u16 *)&msg;
        n = func_ov107_020c8f44(*(int *)(*state + 0x38c), pSeg, hits);
        p[0] = *(u16 *)(*state + 2);
        ((u8 *)p)[2] = 5;
        ((u8 *)p)[3] = 2;
        func_01ffa724(pSeg->nLength, &pSeg->dir, &beam);
        hit = func_01fff8e8(*(void **)(coll + 0x7c), &pSeg->p0, &beam, pSeg->nRadius, 0);
        if (hit != 0 && hit->nBlocked == 0) {
            Fx32 scratchZ;
            Fx32 scratchY;
            Fx32 scratchX;
            normal.x = hit->pPlane->x;
            normal.y = hit->pPlane->y;
            normal.z = hit->pPlane->z;
            func_01ffd144(hit->nAlong, &beam, &end);
            VEC_Add(&pSeg->p0, &end, &end);
            PACK(msg, scratchX, *(Fx32 *)&end.x, 0);
            PACK(msg, scratchY, *(Fx32 *)&end.y, 3);
            PACK(msg, scratchZ, *(Fx32 *)&end.z, 6);
            func_0202ed60(&msg.pose, &data_02042264, &normal);
            if (*(void (**)(int, HitMsg *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, HitMsg *, int))(*state + 0x24))(*state, &msg, 0x20);
            }
        } else {
            hit = func_01fff920(*(void **)(coll + 0x7c), &pSeg->p0, &beam);
            if (hit != 0 && hit->nBlocked == 0) {
                Fx32 scratchZ;
                Fx32 scratchY;
                Fx32 scratchX;
                normal.x = hit->pPlane->x;
                normal.y = hit->pPlane->y;
                normal.z = hit->pPlane->z;
                func_01ffd144(hit->nAlong, &beam, &end);
                VEC_Add(&pSeg->p0, &end, &end);
                PACK(msg, scratchX, *(Fx32 *)&end.x, 0);
                PACK(msg, scratchY, *(Fx32 *)&end.y, 3);
                PACK(msg, scratchZ, *(Fx32 *)&end.z, 6);
                func_0202ed60(&msg.pose, &data_02042264, &normal);
                if (*(void (**)(int, HitMsg *, int))(*state + 0x24) != 0) {
                    (*(void (**)(int, HitMsg *, int))(*state + 0x24))(*state, &msg, 0x20);
                }
            }
        }
        }
    } else if (pSphere != 0) {
        n = func_ov107_020c8eb8(*(int *)(*state + 0x38c), pSphere, hits);
    }
    for (i = 0; i < n; i++) {
        Vec3 push;
        bit = (u8)(1 << hits[i]->nKind);
        if ((*(u8 *)((char *)state + 0x4c) & bit) != 0) {
            continue;
        }
        VEC_Subtract(&hits[i]->vOrigin74, (Vec3 *)(*state + 0x74), &push);
        push.y = 0;
        func_01ff8d18(&push, &push);
        if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x38c), (u8)state[0x12], &push, 0) != 0) {
            if (pSeg != 0) {
                func_ov223_020d43e4(state, hits[i]->vOrigin74);
            } else if (pSphere != 0) {
                func_ov223_020d43e4(state, pSphere->pos);
            }
            func_ov107_020c5af8(*state, 0x149, 8, (void *)state[1]);
            *(u8 *)((char *)state + 0x4c) |= bit;
        }
    }
}
