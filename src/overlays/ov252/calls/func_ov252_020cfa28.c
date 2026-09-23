/* Sway settle tick of the ov252 actor: the +0xc velocity follows the +0x574 part's +0x2c vector turned
 * by the +0x54 heading, scaled by +0x70 + 0.5, and +0x64 accumulates the frame rate; phase 4 rises at
 * 0.125 until 0.43 and phase 3 sinks until 0.93. Once the partner holds no queued move: a pending turn
 * gives next move 5, phase 0 gives 2; with a reward pending or in phase 5 it faces the target and, in
 * phase 5, a target within the turn cone (020cdb88 under 1.05) marks a pending turn while one outside
 * it (or a +0xb4 hit) makes 0xd current and moves on to 020d1abc. With a turn or reward pending pose 3
 * and motion 2 start and the phase becomes 0 (reward) or 5; otherwise the node goes back to 020cf3b8. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov252_020cdafc(Vec3 *out, int angle, Vec3 *vec);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov252_020cdfe8(int *node, Vec3 *delta, int face);
extern int func_ov252_020cdb88(int *node, Vec3 *v, int angle, int wantAbs);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d1abc(void);
extern void func_ov252_020cf3b8(void);

void func_ov252_020cfa28(int *node)
{
    int *state = (int *)node[1];
    Vec3 delta;
    Vec3 v;
    u8 phase;
    int gap;

    func_ov252_020cdafc(&v, state[0x15], (Vec3 *)(*(int *)(*state + 0x574) + 0x2c));
    *(Vec3 *)(state + 3) = v;
    func_01ffa724(state[0x1c] + 0x800, (Vec3 *)(state + 3), (Vec3 *)(state + 3));
    state[0x19] += *(int *)(node[0] + 0x2c);
    switch (*(u8 *)(*state + 0x579)) {
    case 0:
        break;
    case 4:
        if (state[0x19] <= 0x6e8) {
            state[4] = 0x200;
        }
        break;
    case 3:
        if (state[0x19] <= 0xee0) {
            state[4] = -0x200;
        }
        break;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x2a] != 0) {
        *(u8 *)(*state + 0x1c7) = 5;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    phase = *(u8 *)(*state + 0x579);
    if (phase == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0x28] != 0 || phase == 5) {
        func_ov252_020cdfe8(node, &delta, 0);
        if (*(u8 *)(*state + 0x579) == 5) {
            gap = func_ov252_020cdb88(node, &delta, state[0x15], 1);
            if (state[0x2d] != 0) {
                state[0x2d] = 0;
                *(u8 *)(*state + 0x1c6) = 0xd;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d1abc);
                return;
            }
            if (gap < 0x10c1) {
                state[0x2a] = 1;
            } else {
                *(u8 *)(*state + 0x1c6) = 0xd;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d1abc);
                return;
            }
        }
        if (state[0x2a] != 0 || state[0x28] != 0) {
            func_ov107_020c9264(*state, 3, 0);
            func_ov107_020c9ee8(*(int *)(*state + 0x574), 2, 0);
            if (state[0x28] != 0) {
                *(u8 *)(*state + 0x579) = 0;
            } else {
                *(u8 *)(*state + 0x579) = 5;
            }
        }
    } else {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020cf3b8);
    }
}
