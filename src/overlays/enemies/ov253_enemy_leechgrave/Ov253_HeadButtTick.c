/* Head-butt tick: the +0x18 rate is the frame rate x 6; the nearest target (020cab14) becomes +0xc
 * and the +0x14 heading faces it. The +0x1c timer accumulates the frame rate; at 0.53 reaction 0x16c
 * mode 4 fires once at the +4 point (+0x32). Once the timer is at least half of 0.63 (64-bit ratio,
 * capped at 1), a sphere of twice the radius of the +0x3b4 part's +0x68 volume sweeps the actor
 * list: every entity whose +0x1b4 slot bit is clear in +0x31 and that is a valid target
 * (Ov253_IdIsFree) is pushed 1.0 away from the +4 point (kind 4, on behalf of the +0x384
 * rider); on acceptance the message data_ov253_020d49a8 carries the +0x3ac part's +0x14 point to the
 * +0x24 hook, the slot bit is set and reaction 0x16c mode 5 fires there. Once the +8 idle byte
 * clears, animation 7 plays and the tick hands over to Ov253_WaitTick. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

typedef struct { int value; } Fx32;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { VecFx32 center; int nRadius; } Sphere;

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern int Ov107_FindNearestObject(int obj, int kind);
extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern fx16 FX_Atan2(int y, int x);
extern void Ov107_BuildAndSendUpdate(int owner, int id, int mode, void *at);
extern long long FX_DivFx64c(int num, int den);
extern int Ov107_CollectSphereOverlaps(int owner, Sphere *sphere, int *hits);
extern int Ov253_IdIsFree(int owner, int hit);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern int Ov107_InvokeHitCallback(int hit, int owner, int item, int kind, VecFx32 *push, int z);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const Cmd14 data_ov253_020d49a8;
extern void Ov253_WaitTick(int *node);

void Ov253_HeadButtTick(int *node)
{
    int *state = (int *)node[1];
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    VecFx32 d;
    int hits[4];
    Sphere sphere;
    VecFx32 push;
    long long q;
    int n;
    int i;

    state[6] = *(int *)(node[0] + 0x2c) * 30 / 5;
    state[3] = Ov107_FindNearestObject(*state, 0);
    if (state[3] != 0) {
        VEC_Subtract((void *)(state[3] + 0x190), (void *)state[1], &d);
        state[5] = FX_Atan2(d.x, d.z);
    }
    state[7] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0x32) == 0 && state[7] >= 0x888) {
        Ov107_BuildAndSendUpdate(state[0], 0x16c, 4, (void *)state[1]);
        *((u8 *)state + 0x32) = 1;
    }
    q = FX_DivFx64c(state[7], 0xa22);
    if (q > 0x100000000LL) {
        q = 0x100000000LL;
    }
    if (q >= 0x80000000LL) {
        sphere = *(Sphere *)(**(int **)(*state + 0x3b4) + 0x68);
        n = sphere.nRadius;
        sphere.nRadius = n << 1;
        n = Ov107_CollectSphereOverlaps(*state, &sphere, hits);
        for (i = 0; i < n; i++) {
            Cmd14 msg;
            VecFx32 *at;

            if (((*((u8 *)state + 0x31) >> *(u8 *)(hits[i] + 0x1b4)) & 1) != 0) {
                continue;
            }
            if (Ov253_IdIsFree(*(int *)(*state + 0x384), hits[i]) == 0) {
                continue;
            }
            VEC_Subtract((void *)(hits[i] + 0x190), (void *)state[1], &push);
            VEC_Normalize(&push, &push);
            ScaleVec3Fx12(0x1000, &push, &push);
            if (Ov107_InvokeHitCallback(hits[i], *state, *(int *)(*state + 0x384), 4, &push, 0) == 0) {
                continue;
            }
            msg = data_ov253_020d49a8;
            at = (VecFx32 *)(*(int *)(*state + 0x3ac) + 0x14);
            PACK(msg, scratchX, *(Fx32 *)&at->x, 5);
            PACK(msg, scratchY, *(Fx32 *)&at->y, 8);
            PACK(msg, scratchZ, *(Fx32 *)&at->z, 11);
            if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
            }
            *((u8 *)state + 0x31) |= 1 << *(u8 *)(hits[i] + 0x1b4);
            Ov107_BuildAndSendUpdate(*state, 0x16c, 5, (void *)(*(int *)(*state + 0x3ac) + 0x14));
        }
    }
    if (*(u8 *)state[2] != 0) {
        return;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 7, 0);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), (void *)Ov253_WaitTick);
}
