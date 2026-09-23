/* Sway turn tick of the ov252 actor: +0x64 accumulates the frame rate and the +0xc velocity follows the
 * +0x574 part's +0x2c vector turned by the +0x54 heading, scaled by +0x70 + 0.5. By the +0x579 phase:
 * in phase 0, once the partner holds no queued move it faces the target and the node goes back to
 * 020cf3b8 unless the actor picks a move (020cdef4); in phases 1 and 2 the +0x58 goal turns 0x430 to one
 * side and, once the partner is idle, the turn continues while the target (+0x18 relative to the +8
 * point) is still on the phase's side (020ce42c) with the +0x84 pose replayed; in phases 3 and 4 it
 * rises or sinks at 0.625. Advancing plays the next +0x84 pose, motion 5 (phase 1) or 8 (phase 2),
 * clears +0x64 and moves on to 020cfa28. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov252_020cdafc(Vec3 *out, int angle, Vec3 *vec);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern u8 func_ov252_020ce42c(int *state, Vec3 v);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern int func_ov252_020cdfe8(int *node, Vec3 *delta, int face);
extern int func_ov252_020cdef4(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020cf3b8(void);
extern void func_ov252_020cfa28(void);

void func_ov252_020cf7d8(int *node)
{
    int *state = (int *)node[1];
    int idle = *(u8 *)(state[1] + 0xad) == 0;
    Vec3 d;
    Vec3 delta;
    Vec3 v;
    int actor;

    state[0x19] += *(int *)(node[0] + 0x2c);
    func_ov252_020cdafc(&v, state[0x15], (Vec3 *)(*(int *)(*state + 0x574) + 0x2c));
    *(Vec3 *)(state + 3) = v;
    func_01ffa724(state[0x1c] + 0x800, (Vec3 *)(state + 3), (Vec3 *)(state + 3));
    switch (*(u8 *)(*state + 0x579)) {
    case 1:
    case 2:
        state[0x16] = state[0x15] + (*(u8 *)(*state + 0x579) == 2 ? 0x430 : -0x430);
        d.x = state[6] - ((Vec3 *)state[2])->x;
        d.y = 0;
        d.z = state[8] - ((Vec3 *)state[2])->z;
        if (!idle) {
            return;
        }
        actor = *state;
        if (*(u8 *)(actor + 0x579) == func_ov252_020ce42c(state, d)) {
            func_ov107_020c9264(actor, *((u8 *)state + 0x84), 0);
            if (*(u8 *)(*state + 0x579) == 2) {
                func_ov107_020c9ee8(*(int *)(*state + 0x574), 7, 0);
            } else {
                func_ov107_020c9ee8(*(int *)(*state + 0x574), 4, 0);
            }
            return;
        }
        break;
    case 3:
    case 4:
        state[4] = *(u8 *)(*state + 0x579) == 4 ? 0xa00 : -0xa00;
        if (!idle) {
            return;
        }
        break;
    case 0:
        if (!idle) {
            return;
        }
        func_ov252_020cdfe8(node, &delta, 0);
        if (func_ov252_020cdef4(node) == 0) {
            func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020cf3b8);
        } else {
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        }
        return;
    default:
        return;
    }
    func_ov107_020c9264(*state, ++*((u8 *)state + 0x84), 0);
    switch (*(u8 *)(*state + 0x579)) {
    case 1:
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 5, 0);
        break;
    case 2:
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 8, 0);
        break;
    }
    state[0x19] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020cfa28);
}
