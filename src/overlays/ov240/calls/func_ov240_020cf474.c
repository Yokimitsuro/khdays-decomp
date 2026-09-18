/* Triple-slash tick of the ov240 enemy: the +0x38 timer accumulates the frame-time and fires
 * reaction 0x139 modes 5 (from 0x880), 6 (from 0x1650), 7 (from 0x1dc0) and 8 (from 0x24a8)
 * once each (bits 0-3 of +0x3e) at the +8 point; during the three swing windows (0x16d8-0x1980,
 * 0x1ed0 to +0x220 and 0x2530 to +0x2a8, the last two resetting the +0x3c mask once through
 * bits 4/5) the contact sweep runs with kind 1. The +0x14 velocity is the +0x398 part's +0x2c
 * motion turned by the +0x10 yaw; once the +4 item's +0xad byte clears sub-state 2 is
 * requested and the state ends. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern void func_ov240_020ce5c4(int *state, int kind);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, Mtx33 *m, Vec3 *d);
extern void func_0203c634(int *node, int slot, void *cb);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov240_020cf474(int *node)
{
    int *state = (int *)node[1];
    Mtx33 mtx;
    int t;
    unsigned int idx;

    state[0xe] += *(int *)(*node + 0x2c);
    if ((*(u8 *)((char *)state + 0x3e) & 1) == 0 && state[0xe] >= 0x880) {
        *(u8 *)((char *)state + 0x3e) |= 1;
        func_ov107_020c5af8(*state, 0x139, 5, (void *)state[2]);
    }
    if ((*(u8 *)((char *)state + 0x3e) & 2) == 0 && state[0xe] >= 0x1650) {
        *(u8 *)((char *)state + 0x3e) |= 2;
        func_ov107_020c5af8(*state, 0x139, 6, (void *)state[2]);
    }
    if ((*(u8 *)((char *)state + 0x3e) & 4) == 0 && state[0xe] >= 0x1dc0) {
        *(u8 *)((char *)state + 0x3e) |= 4;
        func_ov107_020c5af8(*state, 0x139, 7, (void *)state[2]);
    }
    if ((*(u8 *)((char *)state + 0x3e) & 8) == 0 && state[0xe] >= 0x24a8) {
        *(u8 *)((char *)state + 0x3e) |= 8;
        func_ov107_020c5af8(*state, 0x139, 8, (void *)state[2]);
    }
    t = state[0xe];
    if (t >= 0x16d8 && t <= 0x1980) {
        func_ov240_020ce5c4(state, 1);
    } else if (t >= 0x1ed0 && t <= 0x1ed0 + 0x220) {
        if ((*(u8 *)((char *)state + 0x3e) & 0x10) == 0) {
            *(u8 *)((char *)state + 0x3e) |= 0x10;
            *(u8 *)(state + 0xf) = 0;
        }
        func_ov240_020ce5c4(state, 1);
    } else if (t >= 0x2530 && t <= 0x2530 + 0x2a8) {
        if ((*(u8 *)((char *)state + 0x3e) & 0x20) == 0) {
            *(u8 *)((char *)state + 0x3e) |= 0x20;
            *(u8 *)(state + 0xf) = 0;
        }
        func_ov240_020ce5c4(state, 1);
    }
    idx = ANG2IDX(state[4]);
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x398) + 0x2c), &mtx, (Vec3 *)(state + 5));
    if (*(u8 *)(state[1] + 0xad) == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
