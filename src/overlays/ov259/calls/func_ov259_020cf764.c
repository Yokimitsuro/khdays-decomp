/* Landing tick of the ov259 actor: after 0x1540 of the +0x68 timer pose 0x1c plays, the landing
 * sound 0x172 fires at the +0x10 point (variant 0x1e after a charged jump, +0x5c bit 0, else 0x1f),
 * the charge flag clears, the actor is knocked back there (mode 1), the timer restarts and the node
 * moves on to 020cf82c. */
typedef struct { int x, y, z; } Vec3;
struct Flags5c { int charged : 1; };

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov259_020cd3c4(int actor, int id, int variant, void *at);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020cf82c(void);

void func_ov259_020cf764(int *node)
{
    int *state = (int *)node[1];

    if ((state[0x1a] += *(int *)(node[0] + 0x2c)) <= 0x1540) {
        return;
    }
    func_ov107_020c9264(*state, 0x1c, 0);
    if (((struct Flags5c *)(state + 0x17))->charged) {
        func_ov259_020cd3c4(*state, 0x172, 0x1e, (void *)state[4]);
    } else {
        func_ov259_020cd3c4(*state, 0x172, 0x1f, (void *)state[4]);
    }
    state[0x17] &= ~1;
    func_ov107_020c0b90(*state, 1, *(Vec3 *)state[4], 0);
    state[0x1a] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020cf82c);
}
