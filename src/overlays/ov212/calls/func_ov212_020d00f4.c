/* Leap tick of the ov212 enemy: the +0x40 timer accumulates the owner's rate and, while it lies
 * in [0x15c8, 0x1ed0], the once-only +0x5a cue spawns effect 6 at the actor's +0x74 position
 * and fires reaction 0x128 mode 8 at the +8 point; the +0x28 velocity is copied to +0x10 and
 * decayed per 0x88 slice of the frame by 1.0 - 0.25 x (slice / 0x88), then the actor's +0x508
 * point lowered by a third of 1.0625 x its +0x80 radius is pushed through cf914 (mode 1). Once
 * the +4 item is idle (+0xad) sub-state 2 is queued and the state ends. Codegen: the drop lives
 * in the same stack aggregate as the pushed vector (the ROM stores it at [sp+0x14] and reloads
 * *state after that store). */
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(int actor, int effect, Vec3 v, int flag);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern int FX_Inv(int num, int den);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov212_020cdb1c(int *state, int mode, Vec3 *v);
extern void func_0203c634(int *node, int slot, void *cb);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov212_020d00f4(int *node)
{
    int *state = (int *)node[1];
    struct { Vec3 v; int nDrop; } push;
    int actor;
    int rem;
    int step;

    state[0x10] += *(int *)(node[0] + 0x2c);
    if (state[0x10] >= 0x15c8 && state[0x10] <= 0x1ed0) {
        if (*(unsigned char *)((char *)state + 0x5a) == 0) {
            actor = *state;
            func_ov107_020c0b90(actor, 6, *(Vec3 *)(actor + 0x74), 0);
            func_ov107_020c5af8(*state, 0x128, 8, (void *)state[2]);
            *(unsigned char *)((char *)state + 0x5a) = 1;
        }
        *(Vec3 *)(state + 4) = *(Vec3 *)(state + 0xa);
        for (rem = *(int *)(node[0] + 0x2c); rem > 0; rem -= 0x88) {
            step = rem <= 0x88 ? rem : 0x88;
            func_01ffa724(0x1000 - FX_Mul(FX_Inv(step, 0x88), 0x400), (Vec3 *)(state + 0xa), (Vec3 *)(state + 0xa));
        }
        push.nDrop = FX_Mul(*(int *)(*state + 0x80), 0x1100);
        push.v = *(Vec3 *)(*state + 0x108 + 0x400);
        push.v.y -= push.nDrop / 3;
        func_ov212_020cdb1c(state, 1, &push.v);
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
