/* Hover tick of an ov252 part: the guard sweep runs (020ce370) and +0x64 accumulates the frame rate;
 * a pending +0x88 start plays pose 0x26, at 1.66 a pending +0x89 cue plays sound 0x148/0xd at the +8
 * point, and at 5.98 pose 0x30 plays, the owner plays effect 0xd at the origin and the node moves on to
 * 020d19b8. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov252_020ce370(int *node);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d19b8(void);
extern const Vec3 data_02041dc8;

void func_ov252_020d18c0(int *node)
{
    int *state = (int *)node[1];

    func_ov252_020ce370(node);
    state[0x19] += *(int *)(node[0] + 0x2c);
    if (*((unsigned char *)state + 0x88) == 1) {
        *((unsigned char *)state + 0x88) -= 1;
        func_ov107_020c9264(*state, 0x26, 0);
    }
    if (state[0x19] >= 0x1a90 && *((unsigned char *)state + 0x89) == 1) {
        *((unsigned char *)state + 0x89) = 0;
        func_ov107_020c5af8(*state, 0x148, 0xd, (void *)state[2]);
    }
    if (state[0x19] < 0x5fa0) {
        return;
    }
    func_ov107_020c9264(*state, 0x30, 0);
    func_ov107_020c0b90(*state, 0xd, data_02041dc8, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d19b8);
}
