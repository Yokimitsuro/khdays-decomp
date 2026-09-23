/* Lunge entry of the ov259 actor: the +0x68 timer clears, +0x2c takes the target's +0x190 point and
 * the actor turns to it from its +0xb0 anchor (+0x78 / +0x7c heading), bit 6 of the +0x60 high byte
 * drops, pose 0x10 plays on the actor and its partner, the shot is armed (020cd628: pose 0xd after
 * 0x660), the body sweeps 0x660-0x908 flat (020d1700, +0x424 = 1, +0x420 = 2), the actor is knocked
 * back at the +0x10 point (mode 9), sound 0x172/0x20 fires there and the node moves on to 020cf324. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int y);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov259_020cd524(int *node, int pose, int mode);
extern void func_ov259_020cd628(int *node, int pose, int delay);
extern void func_ov259_020d1700(int body, int a, int b, Vec3 lift);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov259_020cd3c4(int actor, int id, int variant, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020cf324(void);
extern const Vec3 data_02041dc8;

void func_ov259_020cf1d4(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;

    state[0x1a] = 0;
    *(Vec3 *)(state + 0xb) = *(Vec3 *)(state[2] + 0x190);
    VEC_Subtract((Vec3 *)(state + 0xb), (Vec3 *)(*state + 0xb0), &d);
    state[0x1e] = state[0x1f] = func_020050b4(d.x, d.z);
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0x40) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*state, 0x10, 0);
    func_ov259_020cd524(node, 0x10, 0);
    func_ov259_020cd628(node, 0xd, 0x660);
    func_ov259_020d1700(*(int *)(*state + 0x384), 0x660, 0x908, data_02041dc8);
    *(int *)(*state + 0x424) = 1;
    *(int *)(*state + 0x420) = 2;
    func_ov107_020c0b90(*state, 9, *(Vec3 *)state[4], 0);
    func_ov259_020cd3c4(*state, 0x172, 0x20, (void *)state[4]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020cf324);
}
