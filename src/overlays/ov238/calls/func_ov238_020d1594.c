/* Advance tick of the ov238 actor: the +0x3e0 part's +0x2c vector scaled to 0.70 and turned by the
 * heading drives the +0xc velocity, +0x20 accumulates the frame rate and sounds 0x12e/5 and 0x12e/4 cue
 * after 7 and 19 frames. Once the partner holds no queued move: within 3.0 of the target a lunge starts
 * (pose 0x15, part motion 0xb, cues re-armed, node 020d16e8); out of charges (+0x2d) the walk resets
 * (pose 0xf, motion 5) and also goes to 020d16e8; otherwise the node goes back to 020d1510. */
typedef struct { int x, y, z; } Vec3;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov238_020d0878(int *node);
extern void func_ov238_020d0f0c(int *node, int ticks, int cue, int variant);
extern void func_ov238_020d07f0(int *node, Vec3 *vec);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov238_020d16e8(void);
extern void func_ov238_020d1510(void);

void func_ov238_020d1594(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;
    int dist;

    func_01ffa724(0xb40, (Vec3 *)(*(int *)(*state + 0x3e0) + 0x2c), &v);
    dist = func_ov238_020d0878(node);
    state[8] += *(int *)(node[0] + 0x2c);
    func_ov238_020d0f0c(node, 7, 2, 5);
    func_ov238_020d0f0c(node, 0x13, 1, 4);
    func_ov238_020d07f0(node, &v);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (dist < 0x3000) {
        *((unsigned char *)state + 0x2e) = 1;
        *((unsigned char *)state + 0x31) = 2;
        state[8] = 0;
        func_ov107_020c9264(*state, 0x15, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x3e0), 0xb, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov238_020d16e8);
        return;
    }
    if (*((unsigned char *)state + 0x2d) == 0) {
        *((unsigned char *)state + 0x2e) = 0;
        func_ov107_020c9264(*state, 0xf, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x3e0), 5, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov238_020d16e8);
        return;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov238_020d1510);
}
