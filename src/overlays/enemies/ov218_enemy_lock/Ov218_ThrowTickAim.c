/* Throw tick of the ov218 actor: without a target (020cc900) the node ends. +0x14 accumulates the frame
 * rate; at 0.46 sound 0x135/4 plays once at the +8 point. At 0.6 the throw happens once (+0x40 bit 1):
 * the aim is the target's +0x190 point lifted by its radius, seen from the +0x39c hand and turned back
 * by the +0xc heading, and the first unguarded +0x394 partner is thrown at it (020cdff8, 30 % spin).
 * After the throw, once the partner holds no queued move, the second throw (+0x20) re-runs 020cd658;
 * then the next move is 4. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { int m[9]; } Mtx33;
typedef struct { u16 lo : 8; u16 hi : 8; } flags16;
struct Ov218Actor { char pad[0x394]; int partners[2]; };

extern int Ov218_DistanceToTarget(int *node);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov107_BuildAndSendUpdate(int actor, int bank, int variant, void *at);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const VecFx32 *pIn, const Mtx33 *pMtx, VecFx32 *pOut);
extern void Ov218_PlaceAt(int partner, void *hand, VecFx32 *aim, int spin);
extern void Ov218_AiEnterAnim4IfTarget(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov218_ThrowTickAim(int *node)
{
    int *state = (int *)node[1];
    Mtx33 rot;
    VecFx32 aim;
    int i;

    if (Ov218_DistanceToTarget(node) < 0) {
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[5] += *(int *)(node[0] + 0x2c);
    if (!(*((unsigned char *)state + 0x40) & 1) && state[5] >= 0x770) {
        Ov107_BuildAndSendUpdate(*state, 0x135, 4, (void *)state[2]);
        *((unsigned char *)state + 0x40) |= 1;
    }
    if (!(*((unsigned char *)state + 0x40) & 2)) {
        if (state[5] < 0x990) {
            return;
        }
        if (*(int *)(*state + 0x390) == 0) {
            return;
        }
        aim = *(VecFx32 *)(*(int *)(*state + 0x390) + 0x190);
        aim.y += *(int *)(*(int *)(*state + 0x390) + 0x80);
        VEC_Subtract(&aim, (VecFx32 *)(*state + 0x39c), &aim);
        VEC_Normalize(&aim, &aim);
        {
            int turn = state[3] - FX_Atan2(aim.x, aim.z);
            int idx = ANG2IDX(turn) * 2;

            MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
        }
        MTX_MultVec33(&aim, &rot, &aim);
        for (i = 0; i < 2; i++) {
            int partner = ((struct Ov218Actor *)*state)->partners[i];

            if ((((flags16 *)(partner + 0x60))->lo & 1) == 0) {
                Ov218_PlaceAt(partner, (void *)(*state + 0x39c), &aim, RandNextScaled(0x64) < 0x1e);
                break;
            }
        }
        *((unsigned char *)state + 0x40) |= 2;
        return;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (++state[8] < 2) {
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov218_AiEnterAnim4IfTarget);
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 4;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
