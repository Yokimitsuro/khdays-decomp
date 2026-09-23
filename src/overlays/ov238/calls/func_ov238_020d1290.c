/* Walk tick of the ov238 actor: the +0xc velocity follows the +0x3e0 part's +0x2c vector turned by the
 * heading, +0x20 accumulates the frame rate and sounds 0x12e/5 and 0x12e/4 cue after 10 and 35 frames.
 * Once the partner holds no queued move: a target beyond 20.0 makes it turn back (+0x34 set, pose 0x14,
 * motion 0xa); with charges left (+0x2d) and the target at least 6.0 away a charge restarts (pose 0x12,
 * motion 8) and the walk goes on; otherwise it lunges (pose 0x13, motion 9); both lead to 020d1400. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov238_020d0878(int *node);
extern void func_ov238_020d07f0(int *node, Vec3 *vec);
extern void func_ov238_020d0f0c(int *node, int ticks, int cue, int variant);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov238_020d1400(void);

void func_ov238_020d1290(int *node)
{
    int *state = (int *)node[1];
    int dist = func_ov238_020d0878(node);

    func_ov238_020d07f0(node, (Vec3 *)(*(int *)(*state + 0x3e0) + 0x2c));
    state[8] += *(int *)(node[0] + 0x2c);
    func_ov238_020d0f0c(node, 0xa, 2, 5);
    func_ov238_020d0f0c(node, 0x23, 1, 4);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (dist > 0x5000) {
        state[0xd] = 1;
        *((unsigned char *)state + 0x2e) = 0;
        func_ov107_020c9264(*state, 0x14, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x3e0), 0xa, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov238_020d1400);
        return;
    }
    if (*((unsigned char *)state + 0x2d) != 0 && dist >= 0x1800) {
        *((unsigned char *)state + 0x2d) -= 1;
        state[8] = 0;
        *((unsigned char *)state + 0x31) = 2;
        func_ov107_020c9264(*state, 0x12, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x3e0), 8, 0);
    }
    if (*((unsigned char *)state + 0x2d) != 0 && dist >= 0x1800) {
        return;
    }
    *((unsigned char *)state + 0x2e) = 1;
    *((unsigned char *)state + 0x31) = 2;
    state[8] = 0;
    func_ov107_020c9264(*state, 0x13, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3e0), 9, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov238_020d1400);
}
