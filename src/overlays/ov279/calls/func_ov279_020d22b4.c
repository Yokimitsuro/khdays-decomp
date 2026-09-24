/* Ov279_TickOrbitTarget -- chase tick of the ov279 enemy: re-acquires its target (state[2]); with
 * none it hands off to func_ov279_020d24e8. Otherwise it aims at a point orbiting the target
 * (radius state[0x1a] at angle state[0x19], 3.0 above it), steers the +0x30 direction towards it
 * at most 1.0 long, bobs the +0x60 height along a sine of the +0x5c phase and sets the +0x34
 * vertical speed towards it, and hands off once the +0x50 timer reaches 1.0.
 *
 * FX_Mul must be the SDK-style static inline, not a macro: the macro puts the radius first in the
 * smull and every register after it rotates. */
typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

extern int  func_ov107_020cab14(int actor, int n);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern int  func_01ff8d18(VecFx32 *in, VecFx32 *out);
extern void func_01ffa724(int scale, VecFx32 *in, VecFx32 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov279_020d24e8(int *node);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov279_020d22b4(int *node)
{
    int *state = (int *)node[1];
    int nLimit = *(int *)(*state + 0x13c);
    int target;
    int len;
    int half;
    int height;
    VecFx32 aim;

    state[2] = func_ov107_020cab14(*state, 0);
    target = state[2];
    if (target == 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov279_020d24e8);
        return;
    }
    aim.x = *(int *)(target + 0x74) + FX_Mul(data_0203d210[ANG2IDX(state[0x19]) * 2], state[0x1a]);
    aim.y = *(int *)(target + 0x78) + 0x3000;
    aim.z = *(int *)(target + 0x7c) + FX_Mul(data_0203d210[ANG2IDX(state[0x19]) * 2 + 1], state[0x1a]);
    VEC_Subtract(&aim, (VecFx32 *)state[0x13], (VecFx32 *)(state + 0xc));
    len = func_01ff8d18((VecFx32 *)(state + 0xc), (VecFx32 *)(state + 0xc));
    if (len > 0x1000) {
        len = 0x1000;
    }
    func_01ffa724(len, (VecFx32 *)(state + 0xc), (VecFx32 *)(state + 0xc));
    state[0x17] += *(int *)(*node + 0x2c);
    if (state[0x17] > 0x2000) {
        state[0x17] -= 0x4000;
    }
    half = FX_Mul(state[0x17], 0x3244) / 2;
    height = data_0203d210[ANG2IDX(half) * 2] / 2 + 0x4000;
    state[0x18] = height;
    state[0xd] = nLimit > height ? -0x80 : 0x80;
    state[0x14] += *(int *)(*node + 0x2c);
    if (state[0x14] < 0x1000) {
        return;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov279_020d24e8);
}
