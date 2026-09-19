/* func_ov253_020cd484 -- facing tick: the +0x30 delay runs down while non-negative; the +0xc
 * heading is steered (0203d040) towards the +0x10 target at the +0x14 rate with the +0x18
 * state and published at the actor's +0x448; its unit direction is dotted against the four
 * data_ov253_020d4910 axes and the best-facing one becomes the actor's +0x451 side. */
typedef struct { int x, y, z; } Vec3;
struct Ov253Axes { Vec3 v[4]; };

extern int func_0203d040(int heading, int target, int rate, int *state);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern const struct Ov253Axes data_ov253_020d4910;
extern const short data_0203d210[];

void func_ov253_020cd484(int *node) {
    int *state = (int *)node[1];
    Vec3 dir;
    struct Ov253Axes axes = data_ov253_020d4910;
    int i;
    int best = 0x80000001;
    signed char side = 0;
    unsigned short idx;

    if (state[0xc] >= 0) {
        state[0xc] -= *(int *)(node[0] + 0x2c);
    }
    state[3] = func_0203d040(state[3], state[4], state[5], state + 6);
    *(int *)(*state + 0x448) = state[3];
    idx = (unsigned short)((0x28BE60DB9391LL * state[3] + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
    dir.x = data_0203d210[(idx >> 4) << 1];
    dir.y = 0;
    dir.z = data_0203d210[((idx >> 4) << 1) + 1];
    for (i = 0; i < 4; i++) {
        int dot = VEC_DotProduct(&dir, &axes.v[i]);
        if (best < dot) {
            best = dot;
            side = i;
        }
    }
    *(unsigned char *)(*state + 0x451) = side;
}
