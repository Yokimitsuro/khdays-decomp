/* Buck tick: runs the +0x14 timer and maps it to t in 0..1. The +8 velocity is the cubic
 * Hermite blend of the +0x58 start, the +0x394 mount's +0xb0 position, the +0x40 launch and
 * +0x4c landing tangents (h00 = 2t^3-3t^2+1, h01 = -2t^3+3t^2, h10 = t^3-2t^2+t, h11 = t^3-t^2)
 * relative to the +0x1c anchor; the +0x64 pose slerps by t towards the mount's +0xa0 pose,
 * whose forward (data_02042258) sets the +0x2c / +0x30 headings. At t = 1 bit 1 of the actor's
 * +0x60 high byte and bit 0 of +0x1ae clear, the mount is told to land (020c5c54), the mount's
 * +0x3bc bit 0 is set when exactly one rider counter is left, the actor's +0x3c0 bit 0 is set
 * and the node moves to 020d30f4. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

struct m4 { int w[4]; };
struct Bits3bc { unsigned char b0 : 1; };
struct Bits3c0 { unsigned int b0 : 1; };

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern int FX_Div(int num, int den);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Quat_Slerp(void *a, int s, void *b, void *m);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const VecFx32 data_02042258;
extern void Ov236_RecoveryWaitA(void);

void Ov236_BuckTick(int *node) {
    int *state = (int *)node[1];
    VecFx32 mountPos;
    VecFx32 acc;
    VecFx32 tmp;
    struct m4 pose;
    int t;
    int t2;
    int t3;
    int t2x3;

    state[5] += *(int *)(node[0] + 0x2c);
    mountPos = *(VecFx32 *)(*(int *)(*state + 0x394) + 0xb0);
    t = FX_Div(state[5], 0x1000);
    t2 = FX_Mul(t, t);
    t3 = FX_Mul(t2, t);
    t2x3 = 3 * t2;
    ScaleVec3Fx12(2 * t3 - t2x3 + 0x1000, (VecFx32 *)(state + 0x16), &acc);
    ScaleVec3Fx12(-(t3 + t3) + t2x3, &mountPos, &tmp);
    VEC_Add(&acc, &tmp, &acc);
    ScaleVec3Fx12(t3 - 2 * t2 + t, (VecFx32 *)(state + 0x10), &tmp);
    VEC_Add(&acc, &tmp, &acc);
    ScaleVec3Fx12(t3 - t2, (VecFx32 *)(state + 0x13), &tmp);
    VEC_Add(&acc, &tmp, &acc);
    VEC_Subtract(&acc, (VecFx32 *)state[7], (VecFx32 *)(state + 2));
    Quat_Slerp(&pose, t, state + 0x19, (void *)(*(int *)(*state + 0x394) + 0xa0));
    Vec3TransformViaTempMtx(&tmp, (void *)(*(int *)(*state + 0x394) + 0xa0), &data_02042258);
    state[0xc] = state[0xb] = FX_Atan2(tmp.x, tmp.z);
    if (state[5] < 0x1000) return;
    {
        int actor = *state;
        u16 hw = *(u16 *)(actor + 0x60);
        *(u16 *)(actor + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~2) << 0x18) >> 0x10);
    }
    *(u16 *)(*state + 0x100 + 0xae) &= ~1;
    Ov107_MoveNodeAndRelayout((Actor *)(*state), &mountPos);
    if (!(*(short *)(*state + 0x300 + 0xbc) != 0 && *(short *)(*state + 0x300 + 0xbe) != 0)) {
        if (*(short *)(*state + 0x300 + 0xbc) != 0 || *(short *)(*state + 0x300 + 0xbe) != 0) {
            ((struct Bits3bc *)(*(int *)(*state + 0x394) + 0x3bc))->b0 = 1;
        }
    }
    ((struct Bits3c0 *)(*state + 0x3c0))->b0 = 1;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov236_RecoveryWaitA);
}
