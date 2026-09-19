/* Carry tick of the ov266 enemy. Idle means the +0x57c speed is at most 0x200 with the +4 item
 * finished (+0xad). While a +0x5ac order and the +0xc carried actor exist: if the carried actor
 * flags bit 15 of its +0x464 word, the +0x5d4 handle's +0xb0 position is raised by its radius and
 * probed straight down by twice that (a landing hit moves the point onto the floor) and the
 * carried actor's +0x20 node is placed there; when idle it is then dropped (020ad8e0), the pass
 * 020d0200 runs, +0x64 is set, sub-state 0xc queued and the state ends. Without the flag the
 * +0x50 timer counts the owner's rate and, once past 0x2a8 -- or with nothing to carry -- an idle
 * enemy runs the pass, queues sub-state 2 and ends. Otherwise the speed decays per 0x88 slice of
 * the frame by 1.0 - 0x140 x (slice / 0x88). */
typedef struct { int x, y, z; } Vec3;
struct Flags464 { char pad[0x464]; unsigned long long flags; };

extern int *func_01fff920(void *world, Vec3 *origin, Vec3 *dir);
extern void func_01ffd144(int scale, Vec3 *in, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0202b450(int node, Vec3 *pos);
extern void func_ov022_020ad8e0(int actor, int a);
extern void func_ov267_020d2020(int *state);
extern void func_0203c634(int *node, int slot, void *cb);
extern int FX_Inv(int num, int den);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov267_020d3508(int *node)
{
    int *state = (int *)node[1];
    Vec3 pos;
    Vec3 from;
    Vec3 down;
    int bIdle = 0;
    char *owner;
    int radius;
    int *hit;
    int rem;
    int step;

    if (*(int *)(*state + 0x57c) <= 0x200 && *(unsigned char *)(state[1] + 0xad) == 0) {
        bIdle = 1;
    }
    if (*(int *)(*state + 0x5ac) != 0 && state[3] != 0) {
        if ((((struct Flags464 *)state[3])->flags & 0x8000) != 0) {
            owner = *(char **)(*state + 4);
            pos = *(Vec3 *)(*(int *)(*state + 0x5d4) + 0xb0);
            radius = *(int *)(*(int *)(*state + 0x5d4) + 0x80);
            from = pos;
            from.y += radius;
            down.x = 0;
            down.y = -radius * 2;
            down.z = 0;
            hit = func_01fff920(*(void **)(owner + 0x7c), &from, &down);
            if (hit != 0 && hit[2] == 0) {
                func_01ffd144(hit[3], &down, &down);
                VEC_Add(&down, &from, &pos);
            }
            func_0202b450(*(int *)(state[3] + 0x20), &pos);
            if (bIdle != 0) {
                func_ov022_020ad8e0(state[3], 0);
                state[3] = 0;
                func_ov267_020d2020(state);
                state[0x19] = 1;
                *(unsigned char *)(*state + 0x1c7) = 0xc;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            goto decay;
        }
        state[0x14] += *(int *)(node[0] + 0x2c);
        if (state[0x14] < 0x2a8) {
            goto decay;
        }
    }
    if (bIdle != 0) {
        func_ov267_020d2020(state);
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
decay:
    for (rem = *(int *)(node[0] + 0x2c); rem > 0; rem -= 0x88) {
        step = rem <= 0x88 ? rem : 0x88;
        *(int *)(*state + 0x57c) = FX_Mul(*(int *)(*state + 0x57c), 0x1000 - FX_Mul(FX_Inv(step, 0x88), 0x140));
    }
}
