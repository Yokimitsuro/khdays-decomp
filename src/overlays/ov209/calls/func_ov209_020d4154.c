/* Double-strike tick of the ov208 enemy (x3 with ov209/ov268). The +0x2c timer accumulates the
 * owner's rate; while it lies in [0x1b28, 0x1ee6] the +0x3c4 part strikes (reaction 0x154 mode 6
 * at its +4 point, once per bit 0 of +0x49) and its +0x68 sphere, scaled 1.5, is swept with
 * kind 0; in [0xded, 0x1199] the +0x3c8 part does the same under bit 1. Once the +4 animator's
 * +0xad flag drops, the actor's +0x1c7 request becomes 2 and the tick is cleared. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov209_020d2dac(int *state, int kind, Sphere *sphere, void *box);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov209_020d4154(int *node)
{
    int *state = (int *)node[1];
    Sphere sphere;

    state[0xb] += *(int *)(*node + 0x2c);
    if (state[0xb] >= 0x1b28 && state[0xb] <= 0x1ee6) {
        if ((*((u8 *)state + 0x49) & 1) == 0) {
            func_ov107_020c5af8(*state, 0x154, 6, (void *)(*(int *)(*state + 0x3c4) + 4));
            *((u8 *)state + 0x49) |= 1;
        }
        sphere = *(Sphere *)(*(int *)(*state + 0x3c4) + 0x68);
        sphere.radius = FX_MUL(sphere.radius, 0x1800);
        func_ov209_020d2dac(state, 0, &sphere, 0);
    }
    if (state[0xb] >= 0xded && state[0xb] <= 0x1199) {
        if ((*((u8 *)state + 0x49) & 2) == 0) {
            func_ov107_020c5af8(*state, 0x154, 6, (void *)(*(int *)(*state + 0x3c8) + 4));
            *((u8 *)state + 0x49) |= 2;
        }
        sphere = *(Sphere *)(*(int *)(*state + 0x3c8) + 0x68);
        sphere.radius = FX_MUL(sphere.radius, 0x1800);
        func_ov209_020d2dac(state, 0, &sphere, 0);
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
