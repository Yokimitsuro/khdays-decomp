/* Idle float tick of the ov119 enemy (x3 with ov272/ov279). The +0x5c phase advances by the owner's
 * rate and wraps past 2.0; the sine of half its product with 3.14, halved and lifted 2.0, becomes the
 * +0x60 bob height and the +0x34 climb is -0x80 while the owner's +0x13c height is above it (else
 * 0x80). A target found by func_ov119_020cca00 (kept at +8) requests sub-state 6 and ends the tick.
 * Once the +0x50 delay runs out, animation 1 plays (looping), the delay is re-rolled in
 * [+0x224, +0x228], the +0x2c rate becomes the frame rate x 3, the +0x1c facing turns to a random
 * heading and the tick hands over to func_ov119_020cd6a0. */
typedef struct { int x, y, z; } Vec3;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

extern int func_ov119_020cca00(int owner);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern int func_02023eb4(int n);
extern void func_0202f188(void *q, const Vec3 *axis, int angle);
extern const short data_0203d210[];
extern const Vec3 data_02042264;
extern void func_ov119_020cd6a0(int *node);

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + func_02023eb4(span + 1);
}

void func_ov119_020cd4d0(int *node)
{
    int *state = (int *)node[1];
    int height = *(int *)(*state + 0x13c);
    int bob;

    state[0x17] += *(int *)(*node + 0x2c);
    if (state[0x17] > 0x2000) {
        state[0x17] -= 0x4000;
    }
    bob = data_0203d210[ANG2IDX(FX_MUL(state[0x17], 0x3244) / 2) * 2] / 2 + 0x2000;
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
    func_ov107_020c9264(*state, 1, 1);
    state[0x14] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
    state[0xb] = *(int *)(*node + 0x2c) * 30 / 10;
    func_0202f188(state + 7, &data_02042264, RandRange(0, 0x168) * 0x3244 / 180);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov119_020cd6a0);
}
