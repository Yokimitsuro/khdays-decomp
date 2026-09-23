/* Back-off tick of the ov272 enemy. Gives up (sub-state 2) once the +8 target
 * leaves the owner's scene, loses its +0x40 bit 1 or has bit 0 of its +0x60 low byte clear.
 * Otherwise the unit direction from the target's +0x74 point to the +0x4c point (its vertical part
 * made positive and divided by 16) is scaled by 1/8 into the +0x30 step and the +0x1c facing turns
 * along it; the +0x5c bob phase advances as in the other ticks. An attack chosen by
 * func_ov272_020d071c ends the tick; beyond 5.0 the tick goes back to func_ov272_020d1d20, and
 * beyond the owner's +0x2d8 leash sub-state 2 is requested. */
typedef struct { int x, y, z; } Vec3;
struct Bits40 { int b0 : 1, b1 : 1; };
struct hw60 { unsigned short lo : 8, hi : 8; };

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0202ed60(void *q, const Vec3 *from, const Vec3 *to);
extern void func_0202f4a4(void *q, void *out);
extern int func_ov272_020d071c(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const Vec3 data_02042258;
extern void func_ov272_020d1d20(int *node);

void func_ov272_020d1af4(int *node)
{
    int target;
    int *state = (int *)node[1];
    int owner;
    Vec3 d;
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
    VEC_Subtract((void *)state[0x13], (void *)(target + 0x74), &d);
    t = state[2];
    o = state[0];
    gap = func_01ff8d18(&d, &d) - *(int *)(t + 0x80) - *(int *)(o + 0x80);
    if (d.y < 0) {
        d.y = -d.y;
    }
    d.y >>= 4;
    state[0x17] += *(int *)(*node + 0x2c);
    if (state[0x17] > 0x2000) {
        state[0x17] -= 0x4000;
    }
    bob = data_0203d210[ANG2IDX(FX_MUL(state[0x17], 0x3244) / 2) * 2] / 2 + 0x3000;
    state[0x18] = bob;
    if (height > bob) {
        state[0xd] = -0x80;
    } else {
        state[0xd] = 0x80;
    }
    func_01ffa724(0x200, &d, (Vec3 *)(state + 0xc));
    func_0202ed60(state + 7, &data_02042258, &d);
    func_0202f4a4(state + 7, state + 7);
    if (func_ov272_020d071c(node) != 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (gap > 0x5000) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov272_020d1d20);
        return;
    }
    if (gap <= *(int *)(*state + 0x2d8)) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
