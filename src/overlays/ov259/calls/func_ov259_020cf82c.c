/* Wind-up tick of the ov259 actor: the +0x68 clock runs up at the frame rate; past 0.5 it resets,
 * effects 0xf and 8 spawn at the +0x10 point, the +0x384 rig opens (020d1764) and brain slot +0x20
 * runs 020cf8e0. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov259_020d1764(int rig, int open);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020cf8e0(void);

void func_ov259_020cf82c(int *node)
{
    int *state = (int *)node[1];

    state[0x1a] += *(int *)(node[0] + 0x2c);
    if (!(state[0x1a] <= 0x7f8)) {
        state[0x1a] = 0;
        func_ov107_020c0b90(*state, 0xf, *(Vec3 *)state[4], 0);
        func_ov107_020c0b90(*state, 8, *(Vec3 *)state[4], 0);
        func_ov259_020d1764(*(int *)(*state + 0x384), 1);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020cf8e0);
        return;
    }
}
