/* Claw throw entry of the ov256 actor: it re-picks its target (020ccd54), pose 7 plays, it is knocked
 * back at the +0xc point (mode 4, 2), the next claw of the +0x43c set (+0x54 counter) is thrown from
 * 2.19 above that point (020d0334), the counter grows and the node moves on to 020cfe2c. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov256_020ccd54(int *node);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov256_020d0334(int claw, Vec3 *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020cfe2c(void);

void func_ov256_020cfd80(int *node)
{
    int *state = (int *)node[1];
    Vec3 at;

    at = *(Vec3 *)state[3];
    at.y += 0x2300;
    func_ov256_020ccd54(node);
    func_ov107_020c9264(*state, 7, 0);
    func_ov107_020c0b90(*state, 4, *(Vec3 *)state[3], 2);
    func_ov256_020d0334(*(int *)(*state + state[0x15] * 4 + 0x43c), &at);
    state[0x15]++;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020cfe2c);
}
