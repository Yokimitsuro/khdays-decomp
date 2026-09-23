/* Recoil tick of the ov259 actor: after 0x1540 of the +0x68 timer it restarts and the actor is
 * knocked back at its +0x10 point (mode 7); the node moves on to 020d0d28. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020d0d28(void);

void func_ov259_020d0cb4(int *node)
{
    int *state = (int *)node[1];

    state[0x1a] += *(int *)(node[0] + 0x2c);
    if (state[0x1a] <= 0x1540) {
        return;
    }
    state[0x1a] = 0;
    func_ov107_020c0b90(*state, 7, *(Vec3 *)state[4], 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020d0d28);
}
