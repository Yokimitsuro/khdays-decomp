/* Trail tick of the ov212 enemy's thrown part (x3 with ov266/ov267). Bit 7 of the owner's +0x60
 * high byte clears. The owner's +0x74 sphere is queried against the +0x38c body's targets; while
 * nothing is hit, each leg of the three-point +0x40 trail (a box as long as the leg, a third of
 * the owner radius wide, upright) is queried too. The first target the 0.5 push (flattened unit
 * direction from the owner) lands on gets the contact point (owner radius along the direction,
 * plus the push, from the sphere centre): reaction 0/0x4f fires at the +4 point, effect 3 spawns
 * there and sub-state 2 ends the tick. Otherwise the +4 point's step since +0x34 is kept, every
 * 0x300 of the +0x2c timer the trail shifts back and restarts at the point, a 0xb message with the
 * step's heading and the packed point goes through the owner's +0x24 hook, and sub-state 2 ends
 * the tick when the step hits a wall, finds no floor within 0x300, or the +0x20 distance reaches
 * 32.0. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { int value; } Fx32;
typedef struct { int w[4]; } Quat;
typedef struct { VecFx32 c; int r; } Sphere;
typedef struct { VecFx32 center; VecFx32 axisX; VecFx32 axisY; VecFx32 axisZ; int extent[3]; } Obb;
typedef struct { u16 id; u8 kind; u8 cmd; Quat q; u8 pos[9]; u8 pad[3]; } Msg32;
struct hw60 { unsigned short lo : 8, hi : 8; };

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern int Ov107_CollectSphereOverlaps(int body, Sphere *src, int *out);
extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int Ov107_CollectCapsuleOverlaps(int body, Obb *query, int *out);
extern int Ov107_InvokeHitCallback(int hit, int a, int b, int kind, VecFx32 *push, int z);
extern void Ov107_BuildAndSendUpdate(int owner, int id, int mode, void *at);
extern void func_ov107_020c0b90(int actor, int a, VecFx32 v, int b);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern fx16 FX_Atan2(int y, int x);
extern void *Collision_CastRay(void *collision, VecFx32 *origin, VecFx32 *dir);
extern int *Collision_CastSphereEx(void *collision, VecFx32 *origin, VecFx32 *dir, int radius, void *ignore);
extern int VEC_Mag(const VecFx32 *v);
extern const VecFx32 data_02042264;

/* The three-point trail at +0x40 of the state. Codegen notes: the leg's far end is addressed as a
 * byte offset from the trail (`i * 12 + 12`, an offset induction variable next to the walker of
 * pts[i]) and the shift loop reads the trail as a member of the state view; the loop tests
 * `i - 1 >= 0` (subs/bpl). */
struct TrailState { char pad[0x40]; VecFx32 pts[3]; };
void Ov212_TrailTick(int *node)
{
    int *state = (int *)node[1];
    int i;
    int n;
    int world = *(int *)(*state + 4);
    Sphere sphere;
    VecFx32 d;
    Quat quat;
    int hits[4];
    Obb obb;
    VecFx32 dir;
    VecFx32 at;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int *floor;

    ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
    sphere = *(Sphere *)(*state + 0x74);
    n = Ov107_CollectSphereOverlaps(*(int *)(*state + 0x38c), &sphere, hits);
    for (i = 0; n == 0 && i + 1 < 3; i++) {
        VecFx32 *cur = &((VecFx32 *)(state + 0x10))[i];

        VEC_Subtract((VecFx32 *)((char *)(state + 0x10) + (i * 12 + 12)), cur, &d);  /* pts[i + 1] */
        obb.extent[2] = VEC_Normalize(&d, &obb.axisZ) / 2;
        if (obb.extent[2] == 0) {
            break;
        }
        obb.axisY = data_02042264;
        VEC_CrossProduct(&obb.axisY, &obb.axisZ, &obb.axisX);
        obb.extent[0] = obb.extent[1] = *(int *)(*state + 0x80) / 3;
        ScaleVec3Fx12(0x800, &d, &obb.center);
        VEC_Add(&obb.center, cur, &obb.center);
        n = Ov107_CollectCapsuleOverlaps(*(int *)(*state + 0x38c), &obb, hits);
    }
    for (i = 0; i < n; i++) {
        VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &dir);
        VEC_Normalize(&dir, &at);
        dir.y = 0;
        VEC_Normalize(&dir, &dir);
        ScaleVec3Fx12(0x800, &dir, &dir);
        if (Ov107_InvokeHitCallback(hits[i], *state, *(int *)(*state + 0x38c), 3, &dir, 0) != 0) {
            ScaleVec3Fx12(*(int *)(*state + 0x80), &at, &at);
            VEC_Add(&at, &dir, &at);
            VEC_Add(&at, &sphere.c, &at);
            Ov107_BuildAndSendUpdate(state[0], 0, 0x4f, (void *)state[1]);
            func_ov107_020c0b90(*(int *)(*state + 0x38c), 3, at, 0);
            *(u8 *)(*state + 0x1c7) = 2;
            SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    VEC_Subtract((void *)state[1], (void *)(state + 0xd), &d);
    *(VecFx32 *)(state + 0xd) = *(VecFx32 *)state[1];
    state[0xb] += *(int *)(*node + 0x2c);
    if (state[0xb] >= 0x300) {
        state[0xb] = 0;
        for (i = 2; i - 1 >= 0; i--) {
            ((struct TrailState *)state)->pts[i] = ((struct TrailState *)state)->pts[i - 1];
        }
        ((struct TrailState *)state)->pts[0] = *(VecFx32 *)state[1];
    }
    QuatFromAxisAngle(&quat, &data_02042264, FX_Atan2(-d.x, -d.z));
    {
        Msg32 msg = {0};
        u16 *p = (u16 *)&msg;

        p[0] = *(u16 *)(*state + 2);
        ((u8 *)p)[2] = 5;
        ((u8 *)p)[3] = 0xb;
        {
            Fx32 *p = (Fx32 *)state[1];
            PACK(msg, scratchX, p[0], 0x14);
            PACK(msg, scratchY, p[1], 0x17);
            PACK(msg, scratchZ, p[2], 0x1a);
        }
        msg.q = quat;
        if (*(void (**)(int, Msg32 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Msg32 *, int))(*state + 0x24))(*state, &msg, 0x20);
        }
    }
    if (Collision_CastRay(*(void **)(world + 0x7c), (VecFx32 *)state[1], &d) != 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    floor = Collision_CastSphereEx(*(void **)(world + 0x7c), (VecFx32 *)state[1], &d, 0x300, 0);
    if (floor != 0 && floor[2] == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[8] += VEC_Mag(&d);
    if (state[8] < 0x20000) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 2;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
