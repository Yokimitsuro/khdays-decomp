/* Chase tick of the ov256 actor: the +0x4c timer accumulates the frame rate; without a target
 * (020ccd54) the node ends. The +0x10 velocity is the +0x450 owner's +0x2c vector turned by its
 * heading (020cd054). Three rage hits (+0x5c) end the rage (+0x80) and queue move 0xe. Once the partner
 * holds no queued move, after 10.0 of chasing the rage ends, the heading snaps to +0x44, the timer and
 * step clear, pose 0x14 plays, the +0x450 part takes motion 6, flag 0x20b7 is set (020235e8, width 8)
 * and the node moves on to 020cf3b4; before that pose 0x13 / motion 5 restart and it is knocked back
 * at the +0xc point (mode 0xe). */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern int func_ov256_020ccd54(int *node);
extern void func_ov256_020cd054(int *out, int param_2, int *vec);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_020235e8(int field, int width, int value);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020cf3b4(void);

void func_ov256_020cf238(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    state[0x13] += *(int *)(node[0] + 0x2c);
    if (func_ov256_020ccd54(node) == 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_ov256_020cd054((int *)&v, (int)node, (int *)(*(int *)(*state + 0x450) + 0x2c));
    *(Vec3 *)(state + 4) = v;
    if (state[0x17] >= 3) {
        state[0x17] = 0;
        state[0x20] = 0;
        *(signed char *)(*state + 0x1c7) = 0xe;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x13] >= 0xa000) {
        state[0x20] = 0;
        state[0x10] = state[0x11];
        state[0x13] = 0;
        state[0x15] = 0;
        func_ov107_020c9264(*state, 0x14, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x450), 6, 0);
        func_020235e8(0x20b7, 8, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020cf3b4);
        return;
    }
    func_ov107_020c9264(*state, 0x13, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x450), 5, 0);
    func_ov107_020c0b90(*state, 0xe, *(Vec3 *)state[3], 0);
}
