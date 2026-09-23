/* Strafe tick of an ov256 helper: the +0x10 velocity is the +0x390 partner's +0x2c vector turned
 * by the +0x54 heading; between 0xbb0 and 0xff0 of the +0x60 timer a sidestep (0.22 across,
 * -0.04 down, mirrored by the partner's +0x394 side flag) is added in the same frame. +0x50 takes
 * 020d1b2c, +0x34 the +0xc point, the timer advances and 020d1400 steers (1, 3). Once the
 * partner's +0x3c item's +0xad byte clears, or the partner's +0x3a0 request is empty, the request
 * clears and the next move is 1. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, Mtx33 *m, Vec3 *d);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov256_020d1b2c(int *node);
extern void func_ov256_020d1400(int *node, int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const Vec3 data_ov256_020d2648;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov256_020d1ed0(int *node)
{
    int *state = (int *)node[1];
    Mtx33 m;
    Vec3 side = data_ov256_020d2648;
    signed char dir;
    unsigned int idx;

    dir = *(unsigned char *)(*state + 0x394) == 0 ? -1 : 1;
    idx = ANG2IDX(state[0x15]);
    MTX_RotY33_(&m, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x390) + 0x2c), &m, (Vec3 *)(state + 4));
    if (state[0x18] > 0xbb0 && state[0x18] < 0xff0) {
        side.x *= dir;
        MTX_MultVec33(&side, &m, &side);
        VEC_Add((Vec3 *)(state + 4), &side, (Vec3 *)(state + 4));
    }
    state[0x14] = func_ov256_020d1b2c(node);
    *(Vec3 *)(state + 0xd) = *(Vec3 *)state[3];
    state[0x18] += *(int *)(node[0] + 0x2c);
    func_ov256_020d1400(node, 1, 3);
    if (*(unsigned char *)(*(int *)(*(int *)(*state + 0x390) + 0x3c) + 0xad) != 0 && *(int *)(*state + 0x3a0) != 0) {
        return;
    }
    *(int *)(*state + 0x3a0) = 0;
    *(signed char *)(*state + 0x1c7) = 1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
