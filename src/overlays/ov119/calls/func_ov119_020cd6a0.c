/* Hover tick of the ov119 enemy (x3 with ov272/ov279). The +0x30 velocity is the owner's forward
 * axis (from its +0xa0 pose) scaled by 1/16. The +0x5c phase advances by the owner's rate and wraps
 * past 2.0; half its product with 3.14 is the angle whose sine, lifted 2.0, becomes the +0x60 bob
 * height, and the +0x34 climb is -0x80 while the owner's +0x13c height is above it (else 0x80). A
 * target found by func_ov119_020cca00 (kept at +8) requests sub-state 6 and ends the tick; otherwise
 * once the +0x50 delay runs out the tick hands over to func_ov119_020cd478. */
typedef struct { int x, y, z; } Vec3;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

extern void func_0202f384(Vec3 *out, const void *m, const Vec3 *in);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov119_020cca00(int owner);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042258;
extern const short data_0203d210[];
extern void func_ov119_020cd478(int *node);

void func_ov119_020cd6a0(int *node)
{
    int *state = (int *)node[1];
    int height = *(int *)(*state + 0x13c);
    int bob;

    func_0202f384((Vec3 *)(state + 0xc), (void *)(*state + 0xa0), &data_02042258);
    func_01ffa724(0x100, (Vec3 *)(state + 0xc), (Vec3 *)(state + 0xc));
    state[0x17] += *(int *)(*node + 0x2c);
    if (state[0x17] > 0x2000) {
        state[0x17] -= 0x4000;
    }
    bob = data_0203d210[ANG2IDX(FX_MUL(state[0x17], 0x3244) / 2) * 2] + 0x2000;
    state[0x18] = bob;
    state[0xd] = height > bob ? -0x80 : 0x80;
    state[2] = func_ov119_020cca00(*state);
    if (state[2] != 0) {
        *(unsigned char *)(*state + 0x1c7) = 6;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0x14] -= *(int *)(*node + 0x2c);
    if (state[0x14] > 0) {
        return;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov119_020cd478);
}
