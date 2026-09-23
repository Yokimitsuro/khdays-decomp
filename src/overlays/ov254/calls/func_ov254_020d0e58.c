/* Carry tick: the +0x44 timer accumulates the frame rate; the +0xc velocity is the +0x430
 * partner's +0x2c vector turned by the +0x30 yaw and scaled by the +0x54 drop / 20.0. At 0xff0
 * (+0x70 bit 0) the actor is knocked back at its feet (020cdbbc, side 1) and in place (mode 0xa)
 * and the +0x464 helper is started (020d5310); at 0x17e8 (bit 1) that helper is stopped
 * (020d532c) and at 0x5fa0 (bit 2) the +0x45c partner is resumed (020d2050). Once the +4 item's
 * +0xad byte clears +0x78 is cleared, move 0xb is prepared (020cd920), the +0x3c grip becomes
 * 8.0 (rider) or 15.0 and the next move is 4. Otherwise, before 0x2000, every 0x580 of the +0x40
 * countdown knocks the actor back in place again. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, Mtx33 *m, Vec3 *d);
extern int FX_Inv(int num, int den);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_ov254_020cdbbc(int actor, int side);
extern void func_ov254_020d5310(int helper);
extern void func_ov254_020d532c(int helper);
extern void func_ov254_020d2050(int partner);
extern void func_ov254_020cd920(int *self, int arg);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const Vec3 data_02041dc8;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov254_020d0e58(int *node)
{
    int *state = (int *)node[1];
    Mtx33 m;
    unsigned int idx;

    state[0x11] += *(int *)(node[0] + 0x2c);
    idx = ANG2IDX(state[0xc]);
    MTX_RotY33_(&m, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x430) + 0x2c), &m, (Vec3 *)(state + 3));
    func_01ffa724(FX_Inv(state[0x15], 0x14000), (Vec3 *)(state + 3), (Vec3 *)(state + 3));
    if ((*((u8 *)state + 0x70) & 1) == 0 && state[0x11] >= 0xff0) {
        *((u8 *)state + 0x70) |= 1;
        func_ov254_020cdbbc(*state, 1);
        func_ov254_020d5310(*(int *)(*state + 0x464));
        func_ov107_020c0b90(*state, 0xa, data_02041dc8, 0);
    }
    if ((*((u8 *)state + 0x70) & 2) == 0 && state[0x11] >= 0x17e8) {
        *((u8 *)state + 0x70) |= 2;
        func_ov254_020d532c(*(int *)(*state + 0x464));
    }
    if ((*((u8 *)state + 0x70) & 4) == 0 && state[0x11] >= 0x5fa0) {
        *((u8 *)state + 0x70) |= 4;
        func_ov254_020d2050(*(int *)(*state + 0x45c));
    }
    if (*(u8 *)(state[1] + 0xad) == 0) {
        state[0x1e] = 0;
        func_ov254_020cd920(state, 0xb);
        state[0xf] = (state[0x1e] != 0 ? 8 : 0xf) << 12;
        *(signed char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0x11] >= 0x2000) {
        return;
    }
    state[0x10] -= *(int *)(node[0] + 0x2c);
    if (state[0x10] > 0) {
        return;
    }
    func_ov107_020c0b90(*state, 0xa, data_02041dc8, 0);
    state[0x10] = 0x580;
}
