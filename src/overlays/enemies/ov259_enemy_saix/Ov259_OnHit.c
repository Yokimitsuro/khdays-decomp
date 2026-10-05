/* Hit handler of the ov259 enemy. The damage is resolved first; with a +0xc target the +0x78 yaw is
 * checked against the direction from the owner to it (frontal when the dot product is not negative).
 * A frontal hit while the +0x58 dodge is armed turns the owner towards the target's +0x190 point
 * (+0x78 / +0x7c), cancels the damage (result bits 0 and 3), broadcasts message 0xa at the +0x384
 * body and fires reaction 0x3f before sub-state 9. Otherwise the hit is ignored while the stamina
 * (+0x21a) is spent or the +0x1ac bit 0 guard is up; the hit point is recorded, and in the +0x4c
 * shielded phase a third of the damage is taken (also drained from +0x9c). In sub-states 2, 8, 9, 11
 * and 13 a frontal hit dodges the same way with a 5 % chance. The stamina is clamped to the +0x218
 * maximum, the target kept, and a damaging hit (except the 8|0x80 / 0x80 special) plays hurt sound
 * 0x172 alternating on +0xaf (0x22 hits use modes 2/3). Spent stamina sets +0x44 and sub-state 3; an
 * exhausted shield (+0x9c) drops the +0x50 shield effect and requests sub-state 15. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

struct ActorHitEvent {
    unsigned int uFlagsLo : 16;
    unsigned int uFlagsHi : 16;
    VecFx32 vPoint;
    unsigned char pad010[0x14];
    unsigned int uResultLo : 16;
    unsigned int uResultHi : 16;
    int nDamage;
};

extern void VEC_Subtract(void *a, void *b, VecFx32 *d);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *d);
extern int VEC_DotProduct(VecFx32 *a, VecFx32 *b);
extern fx16 FX_Atan2(int y, int x);
extern int Ov107_CalcHitDamage(char *actor, struct ActorHitEvent *hit);
extern void func_ov107_020c0b90(int owner, int mode, VecFx32 at, int flag);
extern void Ov107_BuildAndSendUpdate(int actor, int a, int id, int at);
extern void Ov259_PlaySound(char *actor, int id, int mode, int at);
extern void Ov259_Helper_ReleaseIfReady(int effect);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

int Ov259_OnHit(char *self, int other, struct ActorHitEvent *hit)
{
    int *state = *(int **)(self + 0x214);
    VecFx32 facing;
    VecFx32 d;
    VecFx32 v;
    int frontal;
    int owner;
    unsigned int idx;
    int hp;
    int max;
    unsigned int lo;

    frontal = 0;
    hit->nDamage = Ov107_CalcHitDamage(self, hit);
    if (state[3] != 0) {
        idx = ANG2IDX(state[0x1e]);
        facing.x = data_0203d210[idx * 2];
        facing.y = 0;
        facing.z = data_0203d210[idx * 2 + 1];
        VEC_Subtract((void *)(state[3] + 0x74), (void *)(*state + 0x74), &d);
        VEC_Normalize(&d, &d);
        if (VEC_DotProduct(&facing, &d) >= 0) {
            frontal = 1;
        }
    }
    if (state[0x16] != 0 && frontal != 0) {
        VEC_Subtract((void *)(state[3] + 0x190), (void *)(*state + 0xb0), &v);
        state[0x1e] = state[0x1f] = FX_Atan2(v.x, v.z);
        hit->nDamage = 0;
        hit->uResultLo |= 9;
        owner = *state;
        func_ov107_020c0b90(owner, 0xa, *(VecFx32 *)(*(int *)(owner + 0x384) + 0x74), 0);
        Ov107_BuildAndSendUpdate(*state, 0, 0x3f, state[4]);
        *(u8 *)(*state + 0x1c7) = 9;
        return 1;
    }
    if (*(short *)(self + 0x21a) <= 0) {
        return 0;
    }
    if ((*(u16 *)(self + 0x100 + 0xac) & 1) != 0) {
        return 0;
    }
    *(VecFx32 *)(state + 8) = hit->vPoint;
    if (state[0x13] != 0) {
        hit->nDamage /= 3;
        *(short *)(self + 0x21a) -= hit->nDamage;
    } else {
        switch (*(signed char *)(*state + 0x1c6)) {
        case 2:
        case 8:
        case 9:
        case 11:
        case 13:
            if ((unsigned int)RandNextScaled(100) <= 4 && frontal != 0) {
                hit->nDamage = 0;
                hit->uResultLo |= 9;
                owner = *state;
                func_ov107_020c0b90(owner, 0xa, *(VecFx32 *)(*(int *)(owner + 0x384) + 0x74), 0);
                Ov107_BuildAndSendUpdate(*state, 0, 0x3f, state[4]);
                *(u8 *)(*state + 0x1c7) = 9;
                return 1;
            }
            break;
        }
        *(short *)(self + 0x21a) -= hit->nDamage;
    }
    max = *(short *)(self + 0x218);
    hp = *(short *)(self + 0x21a);
    if (hp <= max) {
        if (hp < 0) {
            hp = 0;
        }
        max = hp;
    }
    *(short *)(self + 0x21a) = max;
    state[3] = other;
    if (state[0x13] != 0) {
        state[0x27] -= hit->nDamage;
    }
    if (hit->nDamage > 0) {
        lo = hit->uFlagsLo;
        if ((lo & 8) == 0 || (lo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((lo & 0x22) != 0) {
                Ov259_PlaySound(self, 0x172, (u16)((++*((u8 *)state + 0xaf) & 1) ? 2 : 3), state[4]);
            } else {
                Ov259_PlaySound(self, 0x172, (u16)((++*((u8 *)state + 0xaf) & 1) == 0), state[4]);
            }
            *((u8 *)state + 0xaf) ^= 1;
        }
    }
    if (*(short *)(self + 0x21a) == 0) {
        state[0x11] = 1;
        *(u8 *)(*state + 0x1c7) = 3;
        return 1;
    }
    if (state[0x27] <= 0 && state[0x13] != 0) {
        if (state[0x14] != 0) {
            Ov259_Helper_ReleaseIfReady(*(int *)(*state + 0x384));
            state[0x14] = 0;
        }
        state[0x27] = 0;
        *(u8 *)(*state + 0x1c7) = 0xf;
    }
    return 1;
}
