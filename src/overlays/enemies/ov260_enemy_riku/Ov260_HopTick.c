/* Hop tick of the ov260 actor: once the partner holds no queued move pose 0x1a plays, its +0x428
 * part takes motion 0xf, it turns to the +0x420 target (+0x64 / +0x68 heading) and the +0x2c velocity
 * becomes the flat direction to it at half the distance in body radii (capped at 1.0) with a 0.5 lift;
 * +0x70 and the +0x7b flag clear and the node moves on to 020cf2d4. Until then the +0x70 timer runs
 * and the cue fires once at 0xcc0 (020cd04c 2). */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *out);
extern int FX_Div(int num, int den);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern void Ov260_MapHeldItemKindToAnim(int actor, int flag);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov260_HopAirTick(void);

static inline void VecSet(VecFx32 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void Ov260_HopTick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;

    if (*(u8 *)(state[1] + 0xad) == 0) {
        int t;

        Ov107_PostTagUpdate((Actor *)(*state), 0x1a, 0);
        Ov107_StartAnim(*(int *)(*state + 0x428), 0xf, 0);
        VEC_Subtract((VecFx32 *)(*(int *)(*state + 0x420) + 0x190), (VecFx32 *)state[4], &d);
        state[0x19] = state[0x1a] = FX_Atan2(d.x, d.z);
        d.y = 0;
        t = FX_Div(VEC_Normalize(&d, &d), *(int *)(*state + 0x80));
        if (t > 0x1000) {
            t = 0x1000;
        }
        ScaleVec3Fx12(FX_MUL(t, 0x800), &d, &d);
        VecSet((VecFx32 *)(state + 0xb), d.x, 0x800, d.z);
        state[0x1c] = 0;
        *((u8 *)state + 0x7b) = 0;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov260_HopAirTick);
    } else {
        state[0x1c] += *(int *)(node[0] + 0x2c);
        if ((*((u8 *)state + 0x7b) & 1) == 0 && state[0x1c] >= 0xcc0) {
            *((u8 *)state + 0x7b) |= 1;
            Ov260_MapHeldItemKindToAnim(*state, 2);
        }
    }
}
