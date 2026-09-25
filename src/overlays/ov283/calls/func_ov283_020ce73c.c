/* Volley tick of the ov283 actor: the +0x48 clock runs up at the frame rate and the +0x10 velocity
 * swings along the +0x38 heading turned a quarter back (0.3125 flat, then lifted 0.375); with both
 * volleys done (+0x68 >= 2) the actor recovers (020ce8c8). Each volley fires once the clock passes
 * its step (2 then 5 x 0x88): a launch (020cc9e0) that finds no free helper ends in 020ce918,
 * otherwise the volley counts; past 0x440 the clock resets and the actor recovers. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int v[2]; } Steps;
struct Ov283VolleyTmpl { u8 pairs[4]; Steps steps; };

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_ov283_020cc9e0(int *node);
extern void func_ov283_020ce8c8(void);
extern void func_ov283_020ce918(void);
extern const short data_0203d210[];
extern const struct Ov283VolleyTmpl data_ov283_020cfb64;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov283_020ce73c(int *node)
{
    int *state = (int *)node[1];
    Steps steps;
    Vec3 lift;
    long long angle;    /* kept 64-bit: the index is derived from it twice (sin and cos) */

    angle = state[0xe] + 0x3244;
    steps = data_ov283_020cfb64.steps;
    state[0x12] += *(int *)(node[0] + 0x2c);
    state[4] = data_0203d210[ANG2IDX(angle) * 2];
    state[5] = 0;
    state[6] = data_0203d210[ANG2IDX(angle) * 2 + 1];
    func_01ffa724(0x500, (Vec3 *)(state + 4), (Vec3 *)(state + 4));
    lift.x = 0;
    lift.y = 0x600;
    lift.z = 0;
    VEC_Add((Vec3 *)(state + 4), &lift, (Vec3 *)(state + 4));
    if ((unsigned int)state[0x1a] >= 2) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov283_020ce8c8);
        return;
    }
    if (state[0x12] > steps.v[state[0x1a]] * 0x88) {
        if (func_ov283_020cc9e0(node) == 0) {
            func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov283_020ce918);
            return;
        }
        state[0x1a]++;
    }
    if (state[0x12] <= 0x440) {
        return;
    }
    state[0x12] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov283_020ce8c8);
}
