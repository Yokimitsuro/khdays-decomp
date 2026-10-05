/* Flight tick of the ov256 actor, by flight mode (+0x6b): 4 heads back to the arena anchor
 * (-0.25, 3.25, -1.5), storing the direction (+0x34), distance (+0x58) and heading (+0x44), with
 * the partner's (020cd054) course mirrored vertically by +0x71; 2 aims (020ccd54) and levels out
 * against the +0x430 partner's height; 0 / 1 circle, the +0x40 heading sweeping a quarter turn
 * per 0x7f8 of the +0x4c timer, rising (0) or sinking (1) by 0.3125; 3 aims and reverses. The
 * velocity then scales by 1.0 + 0.125 per level (+0x45c). Once the +4 item's +0xad byte clears the
 * mode ends when close (2: under 5.0, grounded or out of turns +0x54; 4: under 10.0; 3: beyond
 * 10.0) or, circling, when grounded, out of turns or past its height band; a grounded circle
 * turns away from the side probes (020cdab8, 4.375 out) or half around. Ending plays pose 4 /
 * partner motion 3 and moves on to 020ce574; otherwise each spent turn restarts via 020ce050. As
 * in the original, `turned` is read uninitialised when the first probe misses.
 * Codegen: the tail's `else if` repeats `!done` (ROM predicates the partner test on the done
 * compare: ldreq/ldrbeq/cmpeq), and `grounded` is held as an `int *` read through `(int)` casts,
 * which gives the ROM's r1/r2 split between the mode byte and the flag. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

struct Flag17a { u8 b0 : 1; u8 b1 : 1; };

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);
extern void Ov256_RotateByActorHeading(VecFx32 *out, int *node, void *part);
extern int Ov256_PickTarget(int *node);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern int Ov256_PathProbe(int *node, VecFx32 *probe, int a);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov256_TurnTick(void);
extern void Ov256_AiTakeOff(void);
extern const VecFx32 data_ov256_020d25c4;

static inline void VecSet(VecFx32 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void Ov256_FlightTick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 anchor;
    VecFx32 probe;
    VecFx32 v1;
    VecFx32 v2;
    VecFx32 v3;
    VecFx32 v4;
    int done = 0;
    int turned;
    int *grounded;

    switch (*((u8 *)state + 0x6b)) {
    case 4:
        anchor = data_ov256_020d25c4;
        VEC_Subtract(&anchor, (VecFx32 *)(*state + 0xb0), (VecFx32 *)(state + 0xd));
        state[0x16] = VEC_Normalize((VecFx32 *)(state + 0xd), (VecFx32 *)(state + 0xd));
        if (state[0x16] < 0) {
            state[0x16] = done;
        }
        state[0x11] = FX_Atan2(state[0xd], state[0xf]);
        Ov256_RotateByActorHeading(&v1, node, (void *)(*(int *)(*state + 0x450) + 0x2c));
        *(VecFx32 *)(state + 4) = v1;
        state[5] *= *((signed char *)state + 0x71);
        break;
    case 2:
        Ov256_PickTarget(node);
        Ov256_RotateByActorHeading(&v2, node, (void *)(*(int *)(*state + 0x450) + 0x2c));
        *(VecFx32 *)(state + 4) = v2;
        if (((VecFx32 *)state[3])->y + 0x1000 < *(int *)(*(int *)(*state + 0x430) + 0x194)) {
            state[5] = 0x200;
        } else if (((VecFx32 *)state[3])->x > *(int *)(*(int *)(*state + 0x430) + 0x194) + 0x1000) {
            state[5] = -0x200;
        }
        break;
    case 0:
    case 1:
        state[0x10] = (state[0x13] * 0x1922 / 0x7f8 + state[0x11]) * *((signed char *)state + 0x71);
        state[0x13] += *(int *)(node[0] + 0x2c);
        Ov256_RotateByActorHeading(&v3, node, (void *)(*(int *)(*state + 0x450) + 0x2c));
        *(VecFx32 *)(state + 4) = v3;
        state[5] += 0x500;
        if (*((u8 *)state + 0x6b) == 1) {
            state[5] -= 0xa00;
        }
        break;
    case 3:
        Ov256_PickTarget(node);
        Ov256_RotateByActorHeading(&v4, node, (void *)(*(int *)(*state + 0x450) + 0x2c));
        *(VecFx32 *)(state + 4) = v4;
        ScaleVec3Fx12(-0x1000, (VecFx32 *)(state + 4), (VecFx32 *)(state + 4));
        state[0x11] += 0x3244;
        state[0x10] = state[0x11];
        break;
    }
    ScaleVec3Fx12((*(int *)(*state + 0x45c) << 9) + 0x1000, (VecFx32 *)(state + 4), (VecFx32 *)(state + 4));
    if (*(u8 *)(state[1] + 0xad) == 0) {
        switch (*((u8 *)state + 0x6b)) {
        case 2:
            if (state[0x16] < 0x5000 || state[0x15] == 0 || ((struct Flag17a *)(*state + 0x17a))->b1) {
                done = 1;
            }
            break;
        case 4:
            if (state[0x16] < 0xa000 || state[0x15] == 0) {
                done = 1;
            }
            break;
        case 0:
        case 1:
            grounded = (int *)(((struct Flag17a *)(*state + 0x17a))->b1);
            if (((int)grounded) || state[0x15] == 0 ||
                (*((u8 *)state + 0x6b) == 0 && ((VecFx32 *)state[3])->y > 0x10000) ||
                (*((u8 *)state + 0x6b) == 1 && ((VecFx32 *)state[3])->y < 0xc000)) {
                if (((int)grounded)) {
                    VecSet(&probe, 0x4600, state[5], state[6]);
                    if (Ov256_PathProbe(node, &probe, 0) != 0) {
                        state[0x11] -= 0x1922;
                        state[0x10] = state[0x11];
                        turned = 1;
                    }
                    VecSet(&probe, -0x4600, state[0xe], state[0xf]);
                    if (Ov256_PathProbe(node, &probe, 0) != 0 && !turned) {
                        state[0x11] += 0x1922;
                        state[0x10] = state[0x11];
                        turned = 1;
                    }
                    if (!turned) {
                        state[0x11] += 0x3244;
                        state[0x10] = state[0x11];
                    }
                }
                done = 1;
            }
            break;
        case 3:
            if (state[0x16] > 0xa000 || state[0x15] == 0) {
                done = 1;
            }
            break;
        }
    }
    if (done) {
        Ov107_PostTagUpdate((Actor *)(*state), 4, 0);
        Ov107_StartAnim(*(int *)(*state + 0x450), 3, 0);
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov256_TurnTick);
    } else if (!done && *(u8 *)(state[1] + 0xad) == 0 && state[0x15] != 0) {
        state[0x15]--;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov256_AiTakeOff);
    }
}
