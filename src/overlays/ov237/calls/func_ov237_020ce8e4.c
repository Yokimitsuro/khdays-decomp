/* Enter the lunge of the ov237 actor: the +0x3c aim point is taken from the +0x3d8 partner's +0x2c
 * point (020cdb50); once the +4 rig is idle pose 8 plays, the partner takes pose 4, the +0x30 / +0x34
 * timers and the +0x57 flag clear and the brain waits on 020ce980. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern Vec3 func_ov237_020cdb50(int *node, Vec3 *target);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int actor, int pose, int c);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov237_020ce980(void);

void func_ov237_020ce8e4(int *node)
{
    int *state = (int *)node[1];

    *(Vec3 *)(state + 0xf) = func_ov237_020cdb50(node, (Vec3 *)(*(int *)(*state + 0x3d8) + 0x2c));
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 8, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3d8), 4, 0);
    state[0xc] = 0;
    state[0xd] = 0;
    *((u8 *)state + 0x57) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov237_020ce980);
}
