/* Lunge sequence tick of the ov259 actor: the +0x68 timer accumulates the frame rate; with no
 * target in range (020cdc20) the x / z velocity stops, and the aim is refreshed (020cdcac). The +0x98
 * step fires the body sweeps (020d1700, +0x420 = 5): at 0x550 and 0xaa0 flat, at 0x1100 lifted 0.375
 * after facing the +8 track (+0x78 / +0x7c heading), at 0x17e8 dropped 0.375 while an idle +0x388
 * helper (+0x388 clear) is launched along the heading (020d26e0). Past step 3, once the +4 item's
 * +0xad byte clears, the actor faces the track again and, by the target count against its +0x80
 * range, goes to move 0x12 (over 12x) or 0x10 (over 5x) or plays pose 0x15 with a lifted sweep
 * (+0x420 = 6, +0x424) and restarts via 020d0b6c. The six +0xac flags pulse the cue (020cd2c8 0, 1,
 * 0, 1, 2, 3) at 0x550, 0x7f8, 0xaa0, 0xff0, 0x1298 and 0x1a90. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

typedef struct { int x, y, z, w; } Quat;

extern int Ov259_FaceTargetGap(int *node);
extern void Ov259_RefreshAim(int *node);
extern void Ov259_ForwardSweep(int body, int a, int b, VecFx32 lift);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);
extern void Ov259_LaunchHelper(int helper, int climb, VecFx32 *dir, int heading);
extern void Ov259_MirrorPartnerPose(int *node, int pose, int mode);
extern void Ov259_MapHeldItemKindToAnim(int actor, int flag);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov259_SlamTick(void);
extern const VecFx32 data_02041dc8;
extern const VecFx32 data_02042264;
extern const VecFx32 data_02042258;
extern const VecFx32 data_ov259_020d2f60;
extern const VecFx32 data_ov259_020d2f6c;
extern const VecFx32 data_ov259_020d2f84;

void Ov259_LungeSequenceTick(int *node)
{
    int *state = (int *)node[1];
    int n;

    state[0x1a] += *(int *)(node[0] + 0x2c);
    n = Ov259_FaceTargetGap(node);
    Ov259_RefreshAim(node);
    if (n <= 0) {
        state[5] = 0;
        state[7] = 0;
    }
    switch (state[0x26]) {
    case 0:
        if (state[0x1a] > 0x550) {
            Ov259_ForwardSweep(*(int *)(*state + 0x384), 0x330, 0x550, data_02041dc8);
            *(int *)(*state + 0x420) = 5;
            state[0x26]++;
        }
        break;
    case 1:
        if (state[0x1a] > 0xaa0) {
            Ov259_ForwardSweep(*(int *)(*state + 0x384), 0x2a8, 0x660, data_02041dc8);
            *(int *)(*state + 0x420) = 5;
            state[0x26]++;
        }
        break;
    case 2:
        if (state[0x1a] > 0x1100) {
            VecFx32 d;

            VEC_Subtract((VecFx32 *)(state[2] + 0x190), (VecFx32 *)(*state + 0x74), &d);
            VEC_Normalize(&d, &d);
            state[0x1e] = state[0x1f] = FX_Atan2(d.x, d.z);
            Ov259_ForwardSweep(*(int *)(*state + 0x384), 0x198, 0x6e8, data_ov259_020d2f6c);
            *(int *)(*state + 0x420) = 5;
            state[0x26]++;
        }
        break;
    case 3:
        if (state[0x1a] > 0x17e8) {
            VecFx32 lift = data_ov259_020d2f84;
            int helper = *(int *)(*state + 0x388);

            if (*(int *)(helper + 0x388) == 0) {
                VecFx32 dir;
                Quat q;

                QuatFromAxisAngle(&q, &data_02042264, state[0x1e]);
                Vec3TransformViaTempMtx(&dir, &q, &data_02042258);
                Ov259_LaunchHelper(helper, state[4], &dir, state[0x1e]);
            }
            Ov259_ForwardSweep(*(int *)(*state + 0x384), 0x198, 0x440, lift);
            *(int *)(*state + 0x420) = 5;
            state[0x26]++;
        }
        break;
    default:
        if (*(u8 *)(state[1] + 0xad) == 0) {
            VecFx32 lift = data_ov259_020d2f60;
            VecFx32 d;

            VEC_Subtract((VecFx32 *)(state[2] + 0x190), (VecFx32 *)(*state + 0x74), &d);
            VEC_Normalize(&d, &d);
            state[0x1e] = state[0x1f] = FX_Atan2(d.x, d.z);
            if (n > *(int *)(*state + 0x80) * 12) {
                *(signed char *)(*state + 0x1c7) = 0x12;
                SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            if (n > *(int *)(*state + 0x80) * 5) {
                *(signed char *)(*state + 0x1c7) = 0x10;
                SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            Ov107_PostTagUpdate((Actor *)(*state), 0x15, 0);
            Ov259_MirrorPartnerPose(node, 0x15, 0);
            Ov259_ForwardSweep(*(int *)(*state + 0x384), 0x2a8, 0x7f8, lift);
            *(int *)(*state + 0x420) = 6;
            *(int *)(*state + 0x424) = 1;
            *((u8 *)state + 0xac) = 0;
            state[0x1a] = 0;
            SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov259_SlamTick);
            return;
        }
        break;
    }
    if ((*((u8 *)state + 0xac) & 1) == 0 && state[0x1a] >= 0x550) {
        *((u8 *)state + 0xac) |= 1;
        Ov259_MapHeldItemKindToAnim(*state, 0);
    }
    if ((*((u8 *)state + 0xac) & 2) == 0 && state[0x1a] >= 0x7f8) {
        *((u8 *)state + 0xac) |= 2;
        Ov259_MapHeldItemKindToAnim(*state, 1);
    }
    if ((*((u8 *)state + 0xac) & 4) == 0 && state[0x1a] >= 0xaa0) {
        *((u8 *)state + 0xac) |= 4;
        Ov259_MapHeldItemKindToAnim(*state, 0);
    }
    if ((*((u8 *)state + 0xac) & 8) == 0 && state[0x1a] >= 0xff0) {
        *((u8 *)state + 0xac) |= 8;
        Ov259_MapHeldItemKindToAnim(*state, 1);
    }
    if ((*((u8 *)state + 0xac) & 0x10) == 0 && state[0x1a] >= 0x1298) {
        *((u8 *)state + 0xac) |= 0x10;
        Ov259_MapHeldItemKindToAnim(*state, 2);
    }
    if ((*((u8 *)state + 0xac) & 0x20) == 0 && state[0x1a] >= 0x1a90) {
        *((u8 *)state + 0xac) |= 0x20;
        Ov259_MapHeldItemKindToAnim(*state, 3);
    }
}
