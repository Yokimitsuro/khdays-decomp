/* Orbit tick (slow): the +0xc velocity is the +0x430 partner's +0x2c vector turned by the +0x30
 * yaw and scaled by 0.75, kept level. Once the +4 item's +0xad byte clears and no move is pending,
 * a missing target (020cd080) requests move 2; the handler is then cleared. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, Mtx33 *m, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov254_020cd080(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov254_020cee30(int *node)
{
    int *state = (int *)node[1];
    Mtx33 m;
    unsigned int idx = ANG2IDX(state[0xc]);

    MTX_RotY33_(&m, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x430) + 0x2c), &m, (Vec3 *)(state + 3));
    func_01ffa724(0xc00, (Vec3 *)(state + 3), (Vec3 *)(state + 3));
    state[4] = 0;
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (*(signed char *)(*state + 0x100 + 0xc7) == -1 && func_ov254_020cd080(node) == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
