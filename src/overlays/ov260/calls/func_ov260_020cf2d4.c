/* Hop air tick of the ov260 actor: the +0x70 timer accumulates the frame rate, +0x20 follows the
 * +0x2c velocity with the +0x428 part's +0x30 height and the velocity is damped in 0x88 steps of the
 * frame time. Once the partner holds no queued move the first time pose 0x1d plays and the part takes
 * motion 0x11 (+0x7b bit 0); after that, farther than 1.0 (flat) from the +0x420 target it lands at
 * the target's point raised by its +0x13c height plus 3.82 (+0x14), arms the recoil entry (+0xc =
 * 020cf89c) and moves on to 020cf484, otherwise it moves on to the recoil entry directly. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern int FX_Inv(int num, int den);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020cf89c(void);
extern void func_ov260_020cf484(void);

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov260_020cf2d4(int *node)
{
    Vec3 *vel;
    int *state = (int *)node[1];
    Vec3 d;
    int left;

    vel = (Vec3 *)(state + 0xb);
    state[0x1c] += *(int *)(node[0] + 0x2c);
    *(Vec3 *)(state + 8) = *vel;
    state[9] = *(int *)(*(int *)(*state + 0x428) + 0x30);
    for (left = *(int *)(node[0] + 0x2c); left > 0; left -= 0x88) {
        func_01ffa724(0x1000 - FX_MUL(FX_Inv(left <= 0x88 ? left : 0x88, 0x88), 0x11f), vel, vel);
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if ((*((u8 *)state + 0x7b) & 1) == 0) {
        *((u8 *)state + 0x7b) |= 1;
        func_ov107_020c9264(*state, 0x1d, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x428), 0x11, 0);
        return;
    }
    VEC_Subtract((Vec3 *)(*(int *)(*state + 0x420) + 0x190), (Vec3 *)state[4], &d);
    d.y = 0;
    if (func_01ff8d18(&d, &d) > 0x1000) {
        *(Vec3 *)(state + 5) = *(Vec3 *)(*(int *)(*state + 0x420) + 0x190);
        state[6] += *(int *)(*state + 0x13c) + 0x3d2b;
        state[3] = (int)func_ov260_020cf89c;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020cf484);
        return;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020cf89c);
}
