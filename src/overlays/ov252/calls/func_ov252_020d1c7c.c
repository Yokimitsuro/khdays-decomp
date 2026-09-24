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
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct { void *a; void *b; void *c; int d; } CollisionHit;
typedef struct { int v[3]; } Offs3;

extern void func_ov252_020ce370(int *node);
extern int func_ov252_020cdfe8(int *node, Vec3 *delta, int face);
extern int func_02023eb4(int bound);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov252_020cdb88(int *node, Vec3 *v, int angle, int wantAbs);
extern void func_ov107_020c9264(int owner, int pose, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern Vec3 func_ov252_020cdafc(int angle, Vec3 *vec);
extern int func_ov252_020d056c(int *node, int param);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern int func_ov252_020cfc88(int *node);
extern int func_020050b4(int x, int z);
extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern CollisionHit *func_01fff920(void *collision, Vec3 *origin, Vec3 *direction);
extern const short data_0203d210[];
extern const Vec3 data_ov252_020d43d4;
extern const Offs3 data_ov252_020d4344;
extern const Vec3 data_ov252_020d4380;
extern const struct Ring { Vec3 v[10]; } data_ov252_020d4428;
extern void func_ov252_020d25e8(void);
extern void func_ov252_020d26dc(void);

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

/* Random value in [lo, hi]. */
static inline int RandRange(int lo, int hi)
{
    return func_02023eb4(hi - lo + 1) + lo;
}

void func_ov252_020d1c7c(int *node)
{
    int *state = (int *)node[1];
    struct Ring ring;
    Mtx33 rot;
    Vec3 base = data_ov252_020d43d4;
    Vec3 delta;
    Vec3 dir;
    Vec3 from;
    Vec3 to;
    int dist;
    int turn;

    func_ov252_020ce370(node);
    dist = func_ov252_020cdfe8(node, &delta, 0);
    if (state[0x19] < 0x7f8 && state[0x2b] == 0) {
        func_ov252_020cdfe8(node, 0, 1);
        state[0x16] += RandRange(-0x2ca, 0x2ca);
    }
    if (state[0x2b] != 0 && dist > 0x20000) {
        func_ov252_020cdfe8(node, &delta, 1);
    }
    from = *(Vec3 *)state[2];
    to = *(Vec3 *)(*(int *)(*state + 0x4e4) + 0x190);
    to.y = 0;
    from.y = 0;
    VEC_Subtract(&to, &from, &dir);
    func_01ff8d18(&dir, &dir);
    turn = func_ov252_020cdb88(node, &dir, state[0x16], 1);
    if (state[0x2b] == 0 && dist > 0x20000 && turn > 0x1922) {
        state[0x1f] = 0;
        *((u8 *)state + 0x89) = 1;
        state[0x19] = 0;
        func_ov107_020c9264(*state, 0x2d, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 0x1a, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov252_020d25e8);
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
    *(Vec3 *)(state + 3) = func_ov252_020cdafc(state[0x15], &base);
    if (*(int *)(*(int *)(*state + 0x4e4) + 0x194) > *(int *)(state[2] + 4) + 0x380) {
        state[4] = 0x500;
    } else if (*(int *)(*(int *)(*state + 0x4e4) + 0x194) < *(int *)(state[2] + 4) - 0x380) {
        state[4] = -0x500;
    }
    if (state[0x2b] != 0 && *(u8 *)(state[1] + 0xaf) == 0 && *((u8 *)state + 0x88) == 8) {
        *((u8 *)state + 0x88) = 0;
        func_ov107_020c9264(*state, 0x33, 1);
        func_ov107_020c9264(*state, 0x37, 1);
    }
    if (state[0x2b] == 0) {
        state[0x19] += *(int *)(node[0] + 0x2c);
        state[0x1a] += *(int *)(node[0] + 0x2c);
    }
    if ((*((u8 *)state + 0x92) > 5 && state[0x1a] >= 0x400) || (state[0x1a] >= 0x800 && (unsigned int)func_02023eb4(100) < 10)) {
        if (*((u8 *)state + 0x92) != 0 && func_ov252_020d056c(node, 0) == 1) {
            (*((u8 *)state + 0x92))--;
        }
        state[0x1a] = 0;
    }
    if (state[0x2b] != 0 && (state[0x19] += *(int *)(node[0] + 0x2c)) > 0x2000) {
        u16 roll = func_02023eb4(100);
        Offs3 offs;
        u8 nShots;
        signed char i;

        offs = data_ov252_020d4344;
        nShots = roll < 0x1e ? 2 : 1;
        for (i = 0; i < nShots; i++) {
            Vec3 pos = *(Vec3 *)(*(int *)(*state + 0x554) + 0x14);
            Vec3 off = {0, 0, 0};

            off.x = offs.v[i];
            off = func_ov252_020cdafc(state[0x15], &off);
            VEC_Add(&pos, &off, &pos);
            {
                int idx = ANG2IDX(state[0x15] + 0x3244 + RandRange(-0x1922, 0x1922)) * 2;

                delta.x = data_0203d210[idx];
                delta.y = 0;
                delta.z = data_0203d210[idx + 1];
            }
            func_ov107_020c5af8(*state, 0x148, 8, (void *)state[2]);
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
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        if (dist < 0x5000 && *(int *)(*(int *)(*state + 0x4e4) + 0x194) > *(int *)(state[2] + 4)) {
            if (dist < 0x5000) {
                state[0x2d] = 1;
            }
            *(u8 *)(*state + 0x1c7) = 4;
            *(u8 *)(*state + 0x579) = 5;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    if (state[0x2b] != 0) {
        if (((unsigned int)func_02023eb4(100) < 10 && dist > 0x10000) || func_ov252_020cfc88(node) != 0) {
            signed char i;

            ring = data_ov252_020d4428;
            {
                int idx = ANG2IDX(func_020050b4(*(int *)(*(int *)(*state + 0x4e4) + 0x19c), *(int *)(*(int *)(*state + 0x4e4) + 0x1a4))) * 2;

                MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
            }
            for (i = 0; i < 10; i++) {
                int scene = *(int *)(*state + 4);
                Vec3 probe;
                Vec3 ray = data_ov252_020d4380;
                CollisionHit *hit;

                MTX_MultVec33(ring.v + i, &rot, &ring.v[i]);
                ring.v[i].x += RandRange(-0x3000, 0x3000);
                ring.v[i].z += RandRange(-0x3000, 0x3000);
                probe = *(Vec3 *)(*(int *)(*state + 0x4e4) + 0x190);
                probe.x += ring.v[i].x;
                probe.z += ring.v[i].z;
                {
                    int idx = ANG2IDX(state[0x15]) * 2;

                    delta.x = data_0203d210[idx];
                    delta.y = 0;
                    delta.z = data_0203d210[idx + 1];
                }
                probe.y = 0x14000;
                hit = func_01fff920(*(void **)(scene + 0x7c), &probe, &ray);
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
            func_ov107_020c9264(*state, 0x34, 0);
            func_ov107_020c9264(*state, 0x38, 0);
            func_ov107_020c9264(*state, 3, 0);
            func_ov107_020c9ee8(*(int *)(*state + 0x574), 2, 0);
            func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov252_020d26dc);
            return;
        }
    }
    func_ov107_020c9264(*state, 2, 0);
    if (state[0x2b] != 0) {
        func_ov252_020cdfe8(node, 0, 1);
    }
}
