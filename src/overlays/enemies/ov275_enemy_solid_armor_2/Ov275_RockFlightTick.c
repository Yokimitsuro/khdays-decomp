/* Ov275_RockFlightTick = Ov275_RockFlightTick. Thrown-rock flight tick of the ov275 enemy (x4: ov206/ov207/ov274/ov275; this one fires reaction 0x163). The rock falls (the +0x34
 * vertical speed loses 30 x rate x 1/16 per tick, down to -1.0), the +0x3c spin follows the rate,
 * the +0x44 heading the +0x30 velocity, and the step (mirrored while the owner's +0x17a bit 1 is
 * set) moves a 1.5 sphere from the +4 point. Every target it touches for the first time (+0x50
 * kind mask) is pushed away along the flattened direction; a landed push sends the 0xe message of
 * data_ov275_020d6022 with the midpoint through the owner's +0x24 hook, fires reaction 0x163 mode
 * 0xc there and records the kind bit. Each breakable in the world's list gets a 0.5 push request;
 * a broken one reports the 0xe message of data_ov275_020d6084 at the sphere's rim. The rock lands
 * on a wall or floor whose plane is not flagged (bounced 0x200 up along it), when it was already
 * resting, or after 3.0 of flight: the landing message of data_ov275_020d6014 is broadcast with
 * the point, animation 0x10 plays, reaction 0x163 mode 0x10 fires there and the tick hands over
 * to Ov275_ShockwaveTick. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

typedef struct { int value; } Fx32;
typedef struct { VecFx32 c; int r; } Sphere;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { VecFx32 push; u8 b0c; u8 b0d; u8 pad[2]; int team; int mode; int mask; } BreakReq;

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern fx16 FX_Atan2(int y, int x);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int Ov107_CollectSphereOverlaps(int owner, Sphere *src, int *out);
extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern int Ov107_InvokeHitCallback(int hit, int a, int b, int mode, VecFx32 *push, int z);
extern void Ov107_BuildAndSendUpdate(int owner, int id, int mode, void *at);
extern int Ov275_TestEntitiesAgainstRect(void *collision, VecFx32 *pos, int *out);
extern int Ov002_DispatchNodeEvent(int obj, BreakReq *req);
extern int *Collision_CastRay(void *collision, VecFx32 *origin, VecFx32 *dir);
extern void ScaleVec3Fixed27(int plane, VecFx32 *in, VecFx32 *out);
extern void MsgQueue_Post(int to, void *msg, int size);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const VecFx32 data_02042258;
extern const Cmd14 data_ov275_020d6022;
extern const Cmd14 data_ov275_020d6084;
extern const Cmd14 data_ov275_020d6014;
extern void Ov275_ShockwaveTick(int *node);

static inline void VEC_Set(VecFx32 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void Ov275_RockFlightTick(int *node)
{
    /* The hit count and the world pointer live in a one-element array read through an index that
     * is always 0: they only become registers once the index is folded, which is the ROM's
     * register assignment (same device as MsgQueue_Init / ResCache_FindSlot). */
    struct {
        int nHits;
        int world;
    } scan[1];
    int k = 0;
    int *state = (int *)node[1];
    Sphere sphere;
    int hits[4];
    VecFx32 pos;
    VecFx32 push;
    Cmd14 msg;
    VecFx32 at;
    int list[4];
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    Fx32 rimZ;
    Fx32 rimY;
    Fx32 rimX;
    Fx32 posZ;
    Fx32 posY;
    Fx32 posX;
    int i;
    int m;
    int j;
    int done;

    int landed;
    int *wall;

    landed = state[0xd] < 0 && *(int *)(*state + 0x10c) == 0 ? 1 : 0;
    state[0xf] = *(int *)(*node + 0x2c) * 30 / 20;
    done = 0;
    state[0x11] = FX_Atan2(state[0xc], state[0xe]);
    state[9] += *(int *)(*node + 0x2c);
    scan[k].world = *(int *)(*state + 4);
    state[0xd] -= (int)(((long long)(*(int *)(*node + 0x2c) * 30) * 0x100 + 0x800) >> 12);
    if (state[0xd] < -0x1000) {
        state[0xd] = -0x1000;
    }
    *(VecFx32 *)(state + 5) = *(VecFx32 *)(state + 0xc);
    if (((struct { u8 b0 : 1, b1 : 1; } *)(*state + 0x17a))->b1) {
        VEC_Set((VecFx32 *)(state + 5), -state[0xc], state[0xd], -state[0xe]);
    }
    VEC_Add((VecFx32 *)state[1], (VecFx32 *)(state + 5), &sphere.c);
    sphere.r = 0x1800;
    scan[k].nHits = Ov107_CollectSphereOverlaps(*state, &sphere, hits);
    for (i = 0; i < scan[k].nHits; i++) {
        if (((*(u8 *)((char *)state + 0x50) >> *(u8 *)(hits[i] + 0x1b4)) & 1) != 0) {
            continue;
        }
        VEC_Subtract((void *)(hits[i] + 0x74), &sphere.c, &push);
        push.y = 0;
        if (VEC_Normalize(&push, &push) == 0) {
            push = data_02042258;
        }
        ScaleVec3Fx12(0x1000, &push, &push);
        if (Ov107_InvokeHitCallback(hits[i], *state, *state, 2, &push, 0) == 0) {
            continue;
        }
        msg = data_ov275_020d6022;
        VEC_Add((VecFx32 *)(hits[i] + 0x74), &sphere.c, &at);
        ScaleVec3Fx12(0x800, &at, &at);
        PACK(msg, scratchX, *(Fx32 *)&at.x, 5);
        PACK(msg, scratchY, *(Fx32 *)&at.y, 8);
        PACK(msg, scratchZ, *(Fx32 *)&at.z, 11);
        if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
        }
        Ov107_BuildAndSendUpdate(*state, 0x163, 0xc, &at);
        *(u8 *)((char *)state + 0x50) |= 1 << *(u8 *)(hits[i] + 0x1b4);
    }
    m = Ov275_TestEntitiesAgainstRect(*(void **)(scan[k].world + 0x7c), &sphere.c, list);
    for (j = 0; j < m; j++) {
        BreakReq req = {0};
        VecFx32 d;
        VecFx32 rim;
        Cmd14 msg2;

        VEC_Subtract((void *)(list[j] + 0x2c), &sphere.c, &d);
        VEC_Normalize(&d, &d);
        ScaleVec3Fx12(0x800, &d, &req.push);
        req.b0c = 0xff;
        req.b0d = 2;
        req.team = *(u16 *)(*state + 0x200 + 0x9c);
        req.mode = 4;
        req.mask = 1 << *(u8 *)(*state + 0x29a);
        if (*(int *)(list[j] + 0x28) == 0) {
            continue;
        }
        if (Ov002_DispatchNodeEvent(*(int *)(*(int *)(list[j] + 0x28) + 0x158), &req) == 0) {
            continue;
        }
        msg2 = data_ov275_020d6084;
        ScaleVec3Fx12(sphere.r, &d, &rim);
        VEC_Add(&sphere.c, &rim, &rim);
        PACK(msg2, rimX, *(Fx32 *)&rim.x, 5);
        PACK(msg2, rimY, *(Fx32 *)&rim.y, 8);
        PACK(msg2, rimZ, *(Fx32 *)&rim.z, 11);
        if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg2, 0xe);
        }
    }
    wall = Collision_CastRay(*(void **)(scan[k].world + 0x7c), (VecFx32 *)state[1], (VecFx32 *)(state + 5));
    if (wall != 0 && (wall[2] == 0 || (wall[2] != 0 && (*(u16 *)(wall[2] + 0x22) & 0xff) == 0))) {
        pos = *(VecFx32 *)(state + 5);
        ScaleVec3Fixed27(wall[3], &pos, &pos);
        pos.y += 0x200;
        VEC_Add(&pos, (VecFx32 *)state[1], &pos);
        done = 1;
    } else if (landed) {
        pos = *(VecFx32 *)state[1];
        done = 1;
    }
    if (state[9] >= 0x3000) {
        pos = *(VecFx32 *)state[1];
        done = 1;
    }
    if (done == 0) {
        return;
    }
    {
        Cmd14 msg3;

        msg3 = data_ov275_020d6014;
        PACK(msg3, posX, *(Fx32 *)&pos.x, 5);
        PACK(msg3, posY, *(Fx32 *)&pos.y, 8);
        PACK(msg3, posZ, *(Fx32 *)&pos.z, 11);
        msg3.id = *(u16 *)(*state + 2);
        MsgQueue_Post(1, &msg3, 0xe);
    }
    Ov107_PostTagUpdate((Actor *)(*state), 0x10, 0);
    state[9] = 0;
    Ov107_BuildAndSendUpdate(*state, 0x163, 0x10, &pos);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), (void *)Ov275_ShockwaveTick);
}
