/* Cruise tick of the ov252 actor: the guard sweep runs (020ce370) and the target check (020cdfe8)
 * gives the target distance. With a short +0x64 timer and no +0xac guard the +0x58 wander heading takes
 * a random step of up to 0.17; guarded and farther than 32.0 it faces the target. Unguarded, a target
 * farther than 32.0 more than 0x1922 off the heading ends the cruise: +0x7c clears, +0x89 = 1, the timer
 * clears, pose 0x2d and the +0x574 motion 0x1a play and the node moves on to 020d25e8. The +0x70 speed
 * ramps up by the frame rate plus half the timer (capped at 3.0), a third of the frame rate when
 * guarded (capped at 1.125), or bleeds off by a third of the frame rate once +0xb8 is set (at 0.25 the
 * +0xbc stop is set); the +0xc velocity is the data_ov252_020d43d4 base pushed by that speed and turned
 * by the +0x54 heading, rising or sinking at 0.3125 when the target is 0.22 above or below. A guard cue
 * (8) with the partner's +0xaf flag clear plays poses 0x33 / 0x37. Unguarded the timers run; the +0x68
 * reward timer drops an armour piece (020d056c) at 0.25 with more than five left or 10 % of the frames
 * past 0.5. Guarded, every 2.0 one or (30 %) two breaths leave the +0x554 core joint 2.5 to either side
 * (effect 0x148 / 8, blast 0x1b), aimed a random quarter turn off the heading. Once the rig is idle:
 * unguarded, no lift (+0x78) sets +0xb8, a stop picks move 7, and a target within 5.0 and below picks
 * move 4 (+0x579 = 5, +0xb4 set); guarded, 10 % of the time past 16.0 or away from the origin
 * (020cfc88) ten ring points around the target (data_ov252_020d4428, turned by its facing, 3.0 jitter)
 * probe the ground from 20.0 up (data_ov252_020d4380) and mark impacts (effect 0x27), no lift sets
 * +0xb8, and a stop plays poses 0x34 / 0x38 / 3 with motion 2 and moves on to 020d26dc. Otherwise pose
 * 2 plays and, guarded, it faces the target again. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

typedef struct { int m[9]; } Mtx33;
typedef struct { void *a; void *b; void *c; int d; } CollisionHit;
typedef struct { int v[3]; } Offs3;

extern void Ov252_GuardSweep(int *node);
extern int Ov252_CheckTarget(int *node, VecFx32 *delta, int face);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern int Ov252_HeadingDelta(int *node, VecFx32 *v, int angle, int wantAbs);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern VecFx32 Ov252_TurnVecY(int angle, VecFx32 *vec);
extern int Ov252_DropReward(int *node, int param);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Ov107_BuildAndSendUpdate(int actor, int bank, int variant, void *at);
extern void func_ov107_020c0b90(int owner, int mode, VecFx32 at, int flag);
extern int Ov252_IsAwayFromOrigin(int *node);
extern fx16 FX_Atan2(int x, int z);
extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const VecFx32 *pIn, const Mtx33 *pMtx, VecFx32 *pOut);
extern CollisionHit *Collision_CastRay(void *collision, VecFx32 *origin, VecFx32 *direction);
extern const short data_0203d210[];
extern const VecFx32 data_ov252_020d43d4;
extern const Offs3 data_ov252_020d4344;
extern const VecFx32 data_ov252_020d4380;
extern const struct Ring { VecFx32 v[10]; } data_ov252_020d4428;
extern void Ov252_RiseTick(void);
extern void Ov252_GuardedDriftTick(void);

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

/* Random value in [lo, hi]. */
static inline int RandRange(int lo, int hi)
{
    return RandNextScaled(hi - lo + 1) + lo;
}

void Ov252_CruiseTick(int *node)
{
    int *state = (int *)node[1];
    struct Ring ring;
    Mtx33 rot;
    VecFx32 base = data_ov252_020d43d4;
    VecFx32 delta;
    VecFx32 dir;
    VecFx32 from;
    VecFx32 to;
    int dist;
    int turn;

    Ov252_GuardSweep(node);
    dist = Ov252_CheckTarget(node, &delta, 0);
    if (state[0x19] < 0x7f8 && state[0x2b] == 0) {
        Ov252_CheckTarget(node, 0, 1);
        state[0x16] += RandRange(-0x2ca, 0x2ca);
    }
    if (state[0x2b] != 0 && dist > 0x20000) {
        Ov252_CheckTarget(node, &delta, 1);
    }
    from = *(VecFx32 *)state[2];
    to = *(VecFx32 *)(*(int *)(*state + 0x4e4) + 0x190);
    to.y = 0;
    from.y = 0;
    VEC_Subtract(&to, &from, &dir);
    VEC_Normalize(&dir, &dir);
    turn = Ov252_HeadingDelta(node, &dir, state[0x16], 1);
    if (state[0x2b] == 0 && dist > 0x20000 && turn > 0x1922) {
        state[0x1f] = 0;
        *((u8 *)state + 0x89) = 1;
        state[0x19] = 0;
        Ov107_PostTagUpdate((Actor *)(*state), 0x2d, 0);
        Ov107_StartAnim(*(int *)(*state + 0x574), 0x1a, 0);
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), (void *)Ov252_RiseTick);
        return;
    }
    if (state[0x2e] == 0) {
        if (state[0x2b] == 0) {
            state[0x1c] = state[0x1c] + (*(int *)(node[0] + 0x2c) + state[0x19] / 2);
        } else {
            state[0x1c] = state[0x1c] + *(int *)(node[0] + 0x2c) / 3;
        }
        base.z += state[0x1c];
        if (state[0x2b] != 0 && base.z >= 0x1200) {
            base.z = 0x1200;
            state[0x1c] = 0x1200;
        } else if (state[0x2b] == 0 && base.z >= 0x3000) {
            base.z = 0x3000;
            state[0x1c] = 0x3000;
        }
    } else {
        base.z = state[0x1c] -= *(int *)(node[0] + 0x2c) / 3;
        if (base.z <= 0x400) {
            state[0x2f] = 1;
            base.z = 0x400;
        }
    }
    *(VecFx32 *)(state + 3) = Ov252_TurnVecY(state[0x15], &base);
    if (*(int *)(*(int *)(*state + 0x4e4) + 0x194) > *(int *)(state[2] + 4) + 0x380) {
        state[4] = 0x500;
    } else if (*(int *)(*(int *)(*state + 0x4e4) + 0x194) < *(int *)(state[2] + 4) - 0x380) {
        state[4] = -0x500;
    }
    if (state[0x2b] != 0 && *(u8 *)(state[1] + 0xaf) == 0 && *((u8 *)state + 0x88) == 8) {
        *((u8 *)state + 0x88) = 0;
        Ov107_PostTagUpdate((Actor *)(*state), 0x33, 1);
        Ov107_PostTagUpdate((Actor *)(*state), 0x37, 1);
    }
    if (state[0x2b] == 0) {
        state[0x19] += *(int *)(node[0] + 0x2c);
        state[0x1a] += *(int *)(node[0] + 0x2c);
    }
    if ((*((u8 *)state + 0x92) > 5 && state[0x1a] >= 0x400) || (state[0x1a] >= 0x800 && (unsigned int)RandNextScaled(100) < 10)) {
        if (*((u8 *)state + 0x92) != 0 && Ov252_DropReward(node, 0) == 1) {
            (*((u8 *)state + 0x92))--;
        }
        state[0x1a] = 0;
    }
    if (state[0x2b] != 0 && (state[0x19] += *(int *)(node[0] + 0x2c)) > 0x2000) {
        u16 roll = RandNextScaled(100);
        Offs3 offs;
        u8 nShots;
        signed char i;

        offs = data_ov252_020d4344;
        nShots = roll < 0x1e ? 2 : 1;
        for (i = 0; i < nShots; i++) {
            VecFx32 pos = *(VecFx32 *)(*(int *)(*state + 0x554) + 0x14);
            VecFx32 off = {0, 0, 0};

            off.x = offs.v[i];
            off = Ov252_TurnVecY(state[0x15], &off);
            VEC_Add(&pos, &off, &pos);
            {
                int idx = ANG2IDX(state[0x15] + 0x3244 + RandRange(-0x1922, 0x1922)) * 2;

                delta.x = data_0203d210[idx];
                delta.y = 0;
                delta.z = data_0203d210[idx + 1];
            }
            Ov107_BuildAndSendUpdate(*state, 0x148, 8, (void *)state[2]);
            func_ov107_020c0b90(*state, 0x1b, pos, 1);
        }
        state[0x19] = 0;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x2b] == 0) {
        if (state[0x1e] == 0) {
            state[0x2e] = 1;
        }
        if (state[0x2f] != 0) {
            *(u8 *)(*state + 0x1c7) = 7;
            SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        if (dist < 0x5000 && *(int *)(*(int *)(*state + 0x4e4) + 0x194) > *(int *)(state[2] + 4)) {
            if (dist < 0x5000) {
                state[0x2d] = 1;
            }
            *(u8 *)(*state + 0x1c7) = 4;
            *(u8 *)(*state + 0x579) = 5;
            SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    if (state[0x2b] != 0) {
        if (((unsigned int)RandNextScaled(100) < 10 && dist > 0x10000) || Ov252_IsAwayFromOrigin(node) != 0) {
            signed char i;

            ring = data_ov252_020d4428;
            {
                int idx = ANG2IDX(FX_Atan2(*(int *)(*(int *)(*state + 0x4e4) + 0x19c), *(int *)(*(int *)(*state + 0x4e4) + 0x1a4))) * 2;

                MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
            }
            for (i = 0; i < 10; i++) {
                int scene = *(int *)(*state + 4);
                VecFx32 probe;
                VecFx32 ray = data_ov252_020d4380;
                CollisionHit *hit;

                MTX_MultVec33(ring.v + i, &rot, &ring.v[i]);
                ring.v[i].x += RandRange(-0x3000, 0x3000);
                ring.v[i].z += RandRange(-0x3000, 0x3000);
                probe = *(VecFx32 *)(*(int *)(*state + 0x4e4) + 0x190);
                probe.x += ring.v[i].x;
                probe.z += ring.v[i].z;
                {
                    int idx = ANG2IDX(state[0x15]) * 2;

                    delta.x = data_0203d210[idx];
                    delta.y = 0;
                    delta.z = data_0203d210[idx + 1];
                }
                probe.y = 0x14000;
                hit = Collision_CastRay(*(void **)(scene + 0x7c), &probe, &ray);
                if (hit != 0 && hit->c == 0) {
                    int depth = (int)(((long long)hit->d * ray.y) >> 27);
                    int diff;

                    if (depth < 0) {
                        depth = -depth;
                    }
                    diff = depth - probe.y;
                    if (diff < 0) {
                        diff = -diff;
                    }
                    if (diff <= 0x10) {
                        probe.y = 0x100;
                        func_ov107_020c0b90(*state, 0x27, probe, 1);
                    }
                }
            }
        }
        if (state[0x1e] == 0) {
            state[0x2e] = 1;
        }
        if (state[0x2f] != 0) {
            Ov107_PostTagUpdate((Actor *)(*state), 0x34, 0);
            Ov107_PostTagUpdate((Actor *)(*state), 0x38, 0);
            Ov107_PostTagUpdate((Actor *)(*state), 3, 0);
            Ov107_StartAnim(*(int *)(*state + 0x574), 2, 0);
            SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), (void *)Ov252_GuardedDriftTick);
            return;
        }
    }
    Ov107_PostTagUpdate((Actor *)(*state), 2, 0);
    if (state[0x2b] != 0) {
        Ov252_CheckTarget(node, 0, 1);
    }
}
