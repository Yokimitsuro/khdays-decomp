/* Slam entry of the ov259 actor: the timers, step and cue flags clear, +0xa8 and +0x70 clear and
 * +0xae becomes 0x11; sound 0x172/0x22 fires at the +0x10 point, pose 0x12 plays on the actor and
 * its partner (020cd524), the body sweeps 0x908-0xb28 flat (020d1700, +0x420 = 5), +0x94 = 50 and
 * the node moves on to 020d0400. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov259_020cd3c4(int actor, int id, int variant, void *at);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov259_020cd524(int *node, int pose, int mode);
extern void func_ov259_020d1700(int body, int a, int b, Vec3 lift);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020d0400(void);
extern const Vec3 data_02041dc8;

void func_ov259_020d0338(int *node)
{
    int *state = (int *)node[1];

    state[0x1a] = 0;
    state[0x26] = 0;
    *((u8 *)state + 0xac) = 0;
    state[0x2a] = 0;
    *((u8 *)state + 0xae) = 0x11;
    state[0x1c] = 0;
    func_ov259_020cd3c4(*state, 0x172, 0x22, (void *)state[4]);
    func_ov107_020c9264(*state, 0x12, 0);
    func_ov259_020cd524(node, 0x12, 0);
    func_ov259_020d1700(*(int *)(*state + 0x384), 0x908, 0xb28, data_02041dc8);
    *(int *)(*state + 0x420) = 5;
    state[0x25] = 0x32;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020d0400);
}
