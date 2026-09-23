/* Jump entry of the ov259 actor: the timer, step and cue flags clear, +0x94 = 15 and +0x80 = 0x1078;
 * sound 0x172/0x21 fires at the +0x10 point, pose 0xe plays on the actor and its partner, the shot
 * is armed (020cd628: pose 0xc after 0xff0), the body sweeps 0x1078-0x1430 flat (+0x420 = 1) and the
 * node moves on to 020cf5d8. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov259_020cd3c4(int actor, int id, int variant, void *at);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov259_020cd524(int *node, int pose, int mode);
extern void func_ov259_020cd628(int *node, int pose, int delay);
extern void func_ov259_020d1700(int body, int a, int b, Vec3 lift);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020cf5d8(void);
extern const Vec3 data_02041dc8;

void func_ov259_020cf508(int *node)
{
    int *state = (int *)node[1];

    state[0x1a] = 0;
    state[0x26] = 0;
    *((u8 *)state + 0xac) = 0;
    state[0x25] = 0xf;
    state[0x20] = 0x1078;
    func_ov259_020cd3c4(*state, 0x172, 0x21, (void *)state[4]);
    func_ov107_020c9264(*state, 0xe, 0);
    func_ov259_020cd524(node, 0xe, 0);
    func_ov259_020cd628(node, 0xc, 0xff0);
    func_ov259_020d1700(*(int *)(*state + 0x384), 0x1078, 0x1430, data_02041dc8);
    *(int *)(*state + 0x420) = 1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020cf5d8);
}
