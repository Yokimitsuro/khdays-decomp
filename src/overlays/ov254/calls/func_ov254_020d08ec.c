/* Dive tick: the +0x44 timer accumulates the frame rate; between 0x660 and 0x1650 the +0x10 climb
 * eases along a quarter sine of the +0x54 drop, relative to the +8 track's height above the +0x50
 * start. The first tick knocks the actor back at its feet (020cdbbc, +0x70 bit 0); at 0xaa0
 * reaction 0x16d/0x12 fires at the track (+0x70 bit 1). Once the +4 item's +0xad byte clears the
 * next move is 0xb. */
typedef unsigned char u8;

extern void func_ov254_020cdbbc(int actor, int side);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov254_020d08ec(int *node)
{
    int *state = (int *)node[1];
    int t;

    state[0x11] += *(int *)(node[0] + 0x2c);
    t = state[0x11] > 0x1650 ? 0x1650 : (state[0x11] < 0 ? 0 : state[0x11]);
    if (t >= 0x660) {
        state[4] = FX_Mul(data_0203d210[ANG2IDX((t - 0x660) * 0x1922 / 0xff0) * 2], state[0x15]) -
                   (*(int *)(state[2] + 4) - state[0x14]);
    }
    if ((*((u8 *)state + 0x70) & 1) == 0 && state[0x11] >= 0) {
        *((u8 *)state + 0x70) |= 1;
        func_ov254_020cdbbc(*state, -1);
    }
    if ((*((u8 *)state + 0x70) & 2) == 0 && state[0x11] >= 0xaa0) {
        *((u8 *)state + 0x70) |= 2;
        func_ov107_020c5af8(*state, 0x16d, 0x12, (void *)state[2]);
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    *(signed char *)(*state + 0x1c7) = 0xb;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
