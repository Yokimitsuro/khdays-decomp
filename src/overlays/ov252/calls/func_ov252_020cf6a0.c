/* Sway tick of the ov252 actor: +0x64 accumulates the frame rate, the +0xc velocity follows the +0x574
 * part's +0x2c vector turned by the +0x54 heading (height from the part's +0x30) and scaled by +0x70 +
 * 0.5; in phases 3 and 4 (+0x579) after 1.83 it rises (4) or sinks (3) at 0.625. Once the partner holds
 * no queued move the next +0x84 pose plays, the part takes motion 4 (phase 1) or 7 (phase 2), +0x64
 * clears and the node moves on to 020cf7d8. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov252_020cdafc(Vec3 *out, int angle, Vec3 *vec);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020cf7d8(void);

void func_ov252_020cf6a0(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;
    unsigned char phase;

    state[0x19] += *(int *)(node[0] + 0x2c);
    func_ov252_020cdafc(&v, state[0x15], (Vec3 *)(*(int *)(*state + 0x574) + 0x2c));
    *(Vec3 *)(state + 3) = v;
    state[4] = *(int *)(*(int *)(*state + 0x574) + 0x30);
    func_01ffa724(state[0x1c] + 0x800, (Vec3 *)(state + 3), (Vec3 *)(state + 3));
    phase = *(unsigned char *)(*state + 0x579);
    if (!(phase != 3 && phase != 4) && state[0x19] >= 0x1d38) {
        state[4] = phase == 4 ? 0xa00 : -0xa00;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, ++*((unsigned char *)state + 0x84), 0);
    switch (*(unsigned char *)(*state + 0x579)) {
    case 1:
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 4, 0);
        break;
    case 2:
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 7, 0);
        break;
    }
    state[0x19] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020cf7d8);
}
