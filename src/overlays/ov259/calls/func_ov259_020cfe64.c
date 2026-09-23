/* Charge entry of the ov259 actor: it turns to the +8 target (+0x78 / +0x7c heading), pose 0x11
 * plays on the actor and its partner (020cd524), the body sweeps 0x908-0xb28 flat (020d1700,
 * +0x420 = 4), +0x88 = 0.875 and +0x94 = 100, the timers, step and cue flags, +0xa8 and +0x70 clear,
 * +0xae becomes 0x10 and the node moves on to 020cff54. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int y);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov259_020cd524(int *node, int pose, int mode);
extern void func_ov259_020d1700(int body, int a, int b, Vec3 lift);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020cff54(void);
extern const Vec3 data_02041dc8;

void func_ov259_020cfe64(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;

    VEC_Subtract((Vec3 *)(state[2] + 0x190), (Vec3 *)(*state + 0x74), &d);
    func_01ff8d18(&d, &d);
    state[0x1e] = state[0x1f] = func_020050b4(d.x, d.z);
    func_ov107_020c9264(*state, 0x11, 0);
    func_ov259_020cd524(node, 0x11, 0);
    func_ov259_020d1700(*(int *)(*state + 0x384), 0x908, 0xb28, data_02041dc8);
    *(int *)(*state + 0x420) = 4;
    state[0x22] = 0xe00;
    state[0x25] = 100;
    state[0x1a] = 0;
    state[0x26] = 0;
    *((u8 *)state + 0xac) = 0;
    state[0x2a] = 0;
    *((u8 *)state + 0xae) = 0x10;
    state[0x1c] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020cff54);
}
