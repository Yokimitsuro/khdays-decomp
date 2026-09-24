/* Ov272_TickOrbitTarget -- orbit tick of the ov272 enemy (x3 with ov272/ov279). The target is re-acquired into +8 (none:
 * the tick hands over to func_ov272_020d24d8). The goal point sits on the circle of radius +0x68
 * around the target's +0x74 point at the +0x64 angle, lifted 3.0; the +0x30 step heads from the
 * +0x4c point towards it at up to 1.0. The +0x5c bob phase advances (half sine, lifted 3.0, into
 * +0x60, with the +0x34 climb following the owner's +0x13c height), and once the +0x50 timer
 * reaches 1.0 the tick hands over to func_ov272_020d24d8. */
typedef struct { int x, y, z; } Vec3;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
static inline int FX_MUL(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern int func_ov107_020cab14(int owner, int flag);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern void func_ov272_020d24d8(int *node);

void func_ov272_020d22a4(int *node)
{
    int *state = (int *)node[1];
    int height = *(int *)(*state + 0x13c);
    Vec3 goal;
    int target;
    int len;
    int bob;

    state[2] = func_ov107_020cab14(*state, 0);
    target = state[2];
    if (target == 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov272_020d24d8);
        return;
    }
    goal.x = *(int *)(target + 0x74) + FX_MUL(data_0203d210[ANG2IDX(state[0x19]) * 2], state[0x1a]);
    goal.y = *(int *)(target + 0x78) + 0x3000;
    goal.z = *(int *)(target + 0x7c) + FX_MUL(data_0203d210[ANG2IDX(state[0x19]) * 2 + 1], state[0x1a]);
    VEC_Subtract(&goal, (void *)state[0x13], (Vec3 *)(state + 0xc));
    len = func_01ff8d18((Vec3 *)(state + 0xc), (Vec3 *)(state + 0xc));
    if (len > 0x1000) {
        len = 0x1000;
    }
    func_01ffa724(len, (Vec3 *)(state + 0xc), (Vec3 *)(state + 0xc));
    state[0x17] += *(int *)(*node + 0x2c);
    if (state[0x17] > 0x2000) {
        state[0x17] -= 0x4000;
    }
    bob = data_0203d210[ANG2IDX(FX_MUL(state[0x17], 0x3244) / 2) * 2] / 2 + 0x3000;
    state[0x18] = bob;
    state[0xd] = height > bob ? -0x80 : 0x80;
    state[0x14] += *(int *)(*node + 0x2c);
    if (state[0x14] < 0x1000) {
        return;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov272_020d24d8);
}
