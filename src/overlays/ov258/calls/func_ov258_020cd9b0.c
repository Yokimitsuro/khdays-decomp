/* Turn tick (brain slot 2) of the ov258 actor: in move 2 the +0x38 delay runs down; while +0x54 bit 3
 * is set the actor's +0x428 vortex time runs down pulling nearby objects (020cd5c4) and clears the bit
 * when spent. The +0x2c goal heading is capped at 0.26 from straight ahead (020cd8c0), the +0x4c turn
 * rate grows by 2 up to 3/4 of the frame rate and the +0x28 heading (mirrored to the actor's +0x420)
 * turns toward the goal and orients the pose about up. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;
struct Ov258Vortex { char pad[0x428]; int time; };

extern void func_ov258_020cd5c4(int *node);
extern int func_ov258_020cd8c0(int *node, Vec3 *dir, int angle, int absolute);
extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0203c9d0(void *srt, const Quat *rot);
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042264;

void func_ov258_020cd9b0(int *node)
{
    int *state = (int *)node[1];
    Quat q;
    Vec3 fwd;

    if (*(signed char *)(*state + 0x1c6) == 2 && state[0xe] != 0) {
        state[0xe] -= *(int *)(node[0] + 0x2c);
        if (state[0xe] < 0) {
            state[0xe] = 0;
        }
    }
    if (*((u8 *)state + 0x54) & 8) {
        *(int *)(*state + 0x428) -= *(int *)(node[0] + 0x2c);
        func_ov258_020cd5c4(node);
        if (((struct Ov258Vortex *)*state)->time <= 0) {
            ((struct Ov258Vortex *)*state)->time = 0;
            *((u8 *)state + 0x54) -= 8;
        }
    }
    fwd = data_02041dc8;
    if (func_ov258_020cd8c0(node, &fwd, state[0xb], 0) > 0x430) {
        if (state[0xb] > 0) {
            state[0xb] = 0x430;
        } else {
            state[0xb] = -0x430;
        }
    }
    state[0x13] += 2;
    if (state[0x13] > *(int *)(node[0] + 0x2c) * 0x1e / 0x28) {
        state[0x13] = *(int *)(node[0] + 0x2c) * 0x1e / 0x28;
    }
    state[0xa] = func_0203d040(state[0xa], state[0xb], state[0x13], 0);
    *(int *)(*state + 0x420) = state[0xa];
    func_0202f188(&q, &data_02042264, state[0xa]);
    func_0203c9d0((void *)(*state + 0xa0), &q);
}
