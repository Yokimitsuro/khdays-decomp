/* Circle tick of the ov119 enemy (x3 with ov272/ov279). Gives up (sub-state 2) once the +8 target
 * leaves the owner's scene, loses its +0x40 bit 1 or has bit 0 of its +0x60 low byte clear.
 * Otherwise the gap to the target (between the collision radii) is measured, the +0x5c bob phase
 * advances (half sine, lifted 2.0, into +0x60, with the +0x34 climb following the owner's +0x13c
 * height) and the +0x1c facing aims at the target. An attack chosen by func_ov119_020ccb10 ends the
 * tick; beyond 14.0 the tick goes back to func_ov119_020ce318, within 3.0 on to
 * func_ov119_020cdec4, and beyond the owner's +0x2d8 leash sub-state 2 is requested. */
typedef struct { int x, y, z; } Vec3;
struct Bits40 { int b0 : 1, b1 : 1; };
struct hw60 { unsigned short lo : 8, hi : 8; };

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_0203cd7c(int *dst, const Vec3 *a, const Vec3 *b, const void *c);
extern void func_0202ea48(void *dst, const int *src);
extern int func_ov119_020ccb10(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const Vec3 data_02042264;
extern void func_ov119_020ce318(int *node);
extern void func_ov119_020cdec4(int *node);

void func_ov119_020ce0f0(int *node)
{
    int target;
    int *state = (int *)node[1];
    int owner;
    Vec3 d;
    int mtx[9];
    int t;
    int o;
    int gap;
    int height;
    int bob;

    owner = state[0];
    target = state[2];
    height = *(int *)(owner + 0x13c);
    if (*(int *)(target + 4) != *(int *)(owner + 4) || ((struct Bits40 *)(target + 0x40))->b1 == 0
        || (((struct hw60 *)(target + 0x60))->lo & 1) == 0) {
        *(unsigned char *)(owner + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x74), (void *)state[0x13], &d);
    t = state[2];
    o = state[0];
    gap = func_01ff8d18(&d, &d) - *(int *)(t + 0x80) - *(int *)(o + 0x80);
    state[0x17] += *(int *)(*node + 0x2c);
    if (state[0x17] > 0x2000) {
        state[0x17] -= 0x4000;
    }
    bob = data_0203d210[ANG2IDX(FX_MUL(state[0x17], 0x3244) / 2) * 2] / 2 + 0x2000;
    state[0x18] = bob;
    state[0xd] = height > bob ? -0x80 : 0x80;
    func_0203cd7c(mtx, (Vec3 *)(target + 0x74), (Vec3 *)state[0x13], &data_02042264);
    func_0202ea48(state + 7, mtx);
    if (func_ov119_020ccb10(node) != 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (gap > 0xe000) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov119_020ce318);
        return;
    }
    if (gap < 0x3000) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov119_020cdec4);
        return;
    }
    if (gap <= *(int *)(*state + 0x2d8)) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
