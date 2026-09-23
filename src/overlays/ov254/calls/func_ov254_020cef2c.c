/* Walk entry: pose 0 plays (looping), the +0xc / +0x14 velocity is the +0x30 yaw's direction at
 * speed 0.125 (no rise), +0x80 is set, the +0x44 timer clears, the +0x50 start takes the +8
 * track's +4 position and +0x54 the distance to route point 0xb (020cd840); the +0x70 flag clears
 * and the node moves to 020cf064. */
typedef unsigned char u8;

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern int func_ov254_020cd840(int *state, int a);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern void func_ov254_020cf064(void);

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov254_020cef2c(int *node)
{
    int *state = (int *)node[1];

    func_ov107_020c9264(*state, 0, 1);
    state[4] = 0;
    state[3] = FX_Mul(data_0203d210[ANG2IDX(state[0xc]) * 2], 0x200);
    state[5] = FX_Mul(data_0203d210[ANG2IDX(state[0xc]) * 2 + 1], 0x200);
    state[0x20] = 1;
    state[0x11] = 0;
    state[0x14] = *(int *)(state[2] + 4);
    state[0x15] = func_ov254_020cd840(state, 0xb) - state[0x14];
    *((u8 *)state + 0x70) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020cf064);
}
