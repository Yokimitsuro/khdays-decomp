/* Jump wind-up tick of the ov274 enemy. Until flagged (+0x52) the +0x24 timer accumulates the
 * owner's rate and past 0xeee fires reaction 0x163 mode 0xe at the +8 point and sets the
 * flag. Once the +0xc idle byte is clear the overlay's 14-byte position message
 * (data_ov275_020d6030, the +4 point packed as 24-bit values) goes to the owner's +0x24 hook,
 * bit 0 of +0x1ae is raised, animation 0xe plays (mode 1) and the target is re-acquired into
 * +0x10 with the +0x30 direction zeroed: with a target the flattened unit direction towards
 * its +0x190 is taken, or, when that is degenerate, the sine/cosine of the +0x40 heading, and
 * the direction is scaled by a twentieth of the length; y then becomes 1.0, +0x44 takes the
 * heading of the direction and the tick hands over to Ov275_AiBallisticTick. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

typedef struct { int value; } Fx32;
typedef struct { u8 hi, mid, lo; } Fx24;

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

extern void Ov107_BuildAndSendUpdate(int owner, int id, int mode, void *at);
extern int Ov107_FindNearestObject(int owner, int flag);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const PosMsg data_ov275_020d6030;
extern const VecFx32 data_02041dc8;
extern const short data_0203d210[];
extern void Ov275_AiBallisticTick(int *node);

void Ov275_JumpWindupTick(int *node)
{
    int *state = (int *)node[1];
    PosMsg msg;
    VecFx32 d;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    Fx32 *pPos;
    int len;
    unsigned short idx;

    state[9] += *(int *)(node[0] + 0x2c);
    if (*(u8 *)((char *)state + 0x52) == 0 && state[9] >= 0xeee) {
        Ov107_BuildAndSendUpdate(*state, 0x163, 0xe, (void *)state[2]);
        *(u8 *)((char *)state + 0x52) = 1;
    }
    if (*(u8 *)state[3] != 0) {
        return;
    }
    msg = data_ov275_020d6030;
    pPos = (Fx32 *)state[1];
    scratchX = pPos[0];
    PackFx24(&msg.pos[0], scratchX.value);
    scratchY = pPos[1];
    PackFx24(&msg.pos[1], scratchY.value);
    scratchZ = pPos[2];
    PackFx24(&msg.pos[2], scratchZ.value);
    if (*(void (**)(int, PosMsg *, int))(*state + 0x24) != 0) {
        (*(void (**)(int, PosMsg *, int))(*state + 0x24))(*state, &msg, 0xe);
    }
    *(u16 *)(*state + 0x100 + 0xae) |= 1;
    Ov107_PostTagUpdate((Actor *)(*state), 0xe, 1);
    state[4] = Ov107_FindNearestObject(*state, 0);
    *(VecFx32 *)(state + 0xc) = data_02041dc8;
    if (state[4] != 0) {
        VEC_Subtract((VecFx32 *)(state[4] + 0x190), (VecFx32 *)state[1], &d);
        d.y = 0;
        len = VEC_Normalize(&d, (VecFx32 *)(state + 0xc));
        if (len == 0) {
            idx = FX_RadToIdx(state[0x10]);
            state[0xc] = data_0203d210[(idx >> 4) * 2];
            state[0xd] = 0;
            state[0xe] = data_0203d210[(idx >> 4) * 2 + 1];
        }
        ScaleVec3Fx12(len / 20, (VecFx32 *)(state + 0xc), (VecFx32 *)(state + 0xc));
    }
    state[0xd] = 0x1000;
    state[0x11] = FX_Atan2(state[0xc], state[0xe]);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), (void *)Ov275_AiBallisticTick);
}
