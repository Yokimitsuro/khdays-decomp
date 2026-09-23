/* Climb-out tick: the +0x44 timer accumulates the frame rate; the +0x10 climb follows a quarter
 * sine of the +0x54 drop over the timer (clamped to 0..0x2a80), relative to the +8 track's height
 * above the +0x50 start. The first tick knocks the actor back at its feet (020cdbbc, side -1,
 * +0x70 bit 0). At 0x2a80 the +0x3e0 shape loses bit 1, +0x1ae gains bit 0, pose 0xa plays and
 * the +0x430 partner motion 6; the timer, +0x40 and the +0x70 flags clear, the +0xc velocity
 * resets and the +0x54 drop becomes the height from the track to the actor's +0x4d4 floor + 7.7
 * (at least 15.0); the node moves on to 020d0e58. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern void func_ov254_020cdbbc(int actor, int side);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov254_020d0e58(void);
extern const short data_0203d210[];
extern const Vec3 data_02041dc8;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov254_020d0c94(int *node)
{
    int *state = (int *)node[1];
    int t;
    int floor;

    t = state[0x11] += *(int *)(node[0] + 0x2c);
    if (t > 0x2a80) {
        t = 0x2a80;
    } else if (t < 0) {
        t = 0;
    }
    state[4] = FX_Mul(data_0203d210[ANG2IDX(t * 0x1922 / 0x2a80) * 2], state[0x15]) -
               (*(int *)(state[2] + 4) - state[0x14]);
    if ((*((u8 *)state + 0x70) & 1) == 0 && state[0x11] >= 0) {
        *((u8 *)state + 0x70) |= 1;
        func_ov254_020cdbbc(*state, -1);
    }
    if (state[0x11] < 0x2a80) {
        return;
    }
    ((B8 *)(*(int *)(*state + 0x3e0) + 8))->f &= ~2;
    *(u16 *)(*state + 0x100 + 0xae) |= 1;
    func_ov107_020c9264(*state, 0xa, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x430), 6, 0);
    state[0x11] = 0;
    state[0x10] = 0;
    *((u8 *)state + 0x70) = 0;
    *(Vec3 *)(state + 3) = data_02041dc8;
    floor = *(int *)(*state + 0x4d4) + 0x7b31;
    if (floor < 0xf000) {
        floor = 0xf000;
    }
    state[0x15] = floor - *(int *)(state[2] + 4);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020d0e58);
}
