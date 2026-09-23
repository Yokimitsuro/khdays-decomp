/* Charge tick of the ov238 actor: +0x20 accumulates the frame rate and the +0xc velocity follows the
 * +0x3e0 part's +0x2c vector turned by the heading; at 1.06 the cue plays sounds 0x12e/0xd and 0x12e/0xf
 * at the +8 point. Once the partner holds no queued move the +0x2d count drops, the second-to-last
 * charge (+0x2c = 2) fires effect 5 there, the cue re-arms and the timed step (020d0f54, 6 frames)
 * leads on to 020d212c. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov238_020d07f0(int *node, Vec3 *vec);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov238_020d0f54(int *node, int param_2, int param_3, int param_4, void *cb);
extern void func_ov238_020d212c(void);

void func_ov238_020d2020(int *node)
{
    int *state = (int *)node[1];

    state[8] += *(int *)(node[0] + 0x2c);
    func_ov238_020d07f0(node, (Vec3 *)(*(int *)(*state + 0x3e0) + 0x2c));
    if (state[8] >= 0x880 && *((unsigned char *)state + 0x31) == 1) {
        *((unsigned char *)state + 0x31) -= 1;
        func_ov107_020c5af8(*state, 0x12e, 0xd, (void *)state[2]);
        func_ov107_020c5af8(*state, 0x12e, 0xf, (void *)state[2]);
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *((unsigned char *)state + 0x2d) -= 1;
    if (*((unsigned char *)state + 0x2c) == 2) {
        func_ov107_020c0b90(*state, 5, *(Vec3 *)state[2], 0);
        *((unsigned char *)state + 0x2c) -= 1;
    }
    *((unsigned char *)state + 0x31) = 2;
    state[8] = 0;
    func_ov238_020d0f54(node, 6, 2, 0, func_ov238_020d212c);
}
