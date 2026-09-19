/* Idle tick of the ov266 enemy: the +0x57c speed eases towards 1.0 by a 0x140/0x1000 share of
 * the gap; while it is still negative the +0x4f0 position drifts 0x300 towards the +0x5a8
 * target's +0x190 point, otherwise the +0x40 timer counts the owner's rate and past 1.0 hands
 * off to 020d15c0. A pending +0x5b0 order spawns effect 8 at +0x5c0 and queues sub-state 8, a
 * +0x5ac one spawns it at +0x5b4 and queues 7, and a bare +0x5d8 flag queues 7; when a sub-state
 * was queued the +0x5d4 handle is released (020d38cc) and the state ends. */
typedef struct { int x, y, z; } Vec3;

extern void func_0203c634(int *node, int slot, void *cb);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c0b90(int actor, int effect, Vec3 v, int flag);
extern void func_ov212_020d1ad4(int handle);
extern void func_ov212_020cf7bc(int *node);

void func_ov212_020cf630(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;
    int actor;

    *(int *)(*state + 0x57c) += (0x1000 - *(int *)(*state + 0x57c)) * 0x140 / 0x1000;
    if (*(int *)(*state + 0x57c) >= 0) {
        state[0x10] += *(int *)(node[0] + 0x2c);
        if (state[0x10] >= 0x1000) {
            func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov212_020cf7bc);
            return;
        }
    } else {
        VEC_Subtract((Vec3 *)(*(int *)(*state + 0x5a8) + 0x190), (Vec3 *)(*state + 0x4f0), &v);
        func_01ffa724(0x300, &v, &v);
        VEC_Add((Vec3 *)(*state + 0x4f0), &v, (Vec3 *)(*state + 0x4f0));
    }
    actor = *state;
    if (*(int *)(actor + 0x5b0) != 0) {
        func_ov107_020c0b90(actor, 8, *(Vec3 *)(actor + 0x5c0), 0);
        *(unsigned char *)(*state + 0x1c7) = 8;
    } else if (*(int *)(actor + 0x5ac) != 0) {
        func_ov107_020c0b90(actor, 8, *(Vec3 *)(actor + 0x1b4 + 0x400), 0);
        *(unsigned char *)(*state + 0x1c7) = 7;
    } else if (*(int *)(actor + 0x5d8) != 0) {
        *(unsigned char *)(actor + 0x1c7) = 7;
    }
    if (*(signed char *)(*state + 0x1c7) == -1) {
        return;
    }
    func_ov212_020d1ad4(*(int *)(*state + 0x5d4));
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
