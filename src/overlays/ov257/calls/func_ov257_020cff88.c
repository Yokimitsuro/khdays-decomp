/* Landing tick of an ov257 state: the +0x40 rate is the frame rate x 3 and the +0x60 path point
 * is resolved (func_ov257_020ccf98) into the +0x10 step. Once the +0xc idle byte clears, the +0x4c
 * cooldown is re-rolled in [+0x224, +0x228] and sub-state 2 is requested. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov257_020ccf98(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_02023eb4(int n);
extern void func_0203c634(int *node, int slot, void *cb);

static inline int RandRange(int lo, int hi)
{
    int d = hi - lo;

    if (d < 0) {
        d = -d;
    }
    return lo + func_02023eb4(d + 1);
}

void func_ov257_020cff88(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;

    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 10;
    func_ov257_020ccf98(state, state[0x18], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    state[0x13] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
