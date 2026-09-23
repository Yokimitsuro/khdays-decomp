/* Enter the ov258 actor's swing: the +0x30 / +0x34 / +0x3c timers clear, the +0x52 high nibble is 2,
 * +0x50 = 3, the +0x53 step countdown 6 with the +0x44 clock cleared and the +0x52 low nibble 0, the
 * rig switches (020cd028 mode 1), pose 2 plays with effect 1 at the origin, the +0x45c partner arms
 * its 2.16 to 2.32 window (mode 1, 020cfd3c) and the brain waits on 020ce0a0. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 lo : 4; u8 hi : 4; } NibblePair;

extern void func_ov258_020cd028(int *node, int mode);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov258_020cfd3c(int partner, int from, int to, int d);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov258_020ce0a0(void);
extern const Vec3 data_02041dc8;

void func_ov258_020cdfcc(int *node)
{
    int *state = (int *)node[1];

    state[0xc] = 0;
    state[0xd] = 0;
    state[0xf] = 0;
    ((NibblePair *)((u8 *)state + 0x52))->hi = 2;
    *(short *)(state + 0x14) = 3;
    ((NibblePair *)((u8 *)state + 0x53))->lo = 6;
    state[0x11] = 0;
    ((NibblePair *)((u8 *)state + 0x52))->lo = 0;
    func_ov258_020cd028(node, 1);
    func_ov107_020c9264(*state, 2, 0);
    func_ov107_020c0b90(*state, 1, data_02041dc8, 0);
    func_ov258_020cfd3c(*(int *)(*state + 0x45c), 0x2288, 0x2530, 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov258_020ce0a0);
}
