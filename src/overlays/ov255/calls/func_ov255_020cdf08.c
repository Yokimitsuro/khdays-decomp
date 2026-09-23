/* Settle tick of an ov255 state: the +0x40 rate clears and the +0x5c path point is resolved
 * (func_ov255_020ccdac) into the +0x10 step. Once the +0xc idle byte clears a d101 picks the next
 * sub-state -- 0xc below 40; 9 below 80 when the +0x3ec partner is active (bit 1 of its +0x40
 * object's +0x5c) and the path point is closer than 8.0; else 2 -- and the tick ends. */
typedef struct { int x, y, z; } Vec3;
struct Bits5c { int b0 : 1, b1 : 1; };

extern int func_ov255_020ccdac(int *state, int point, Vec3 *dir, int *speed);
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

void func_ov255_020cdf08(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;
    int dist;
    int roll;

    state[0x10] = 0;
    dist = func_ov255_020ccdac(state, state[0x17], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    roll = RandRange(0, 100);
    if (roll < 0x28) {
        *(unsigned char *)(*state + 0x1c7) = 0xc;
    } else if (roll < 0x50
               && ((struct Bits5c *)(*(int *)(*(int *)(*state + 0x3ec) + 0x40) + 0x5c))->b1
               && dist < 0x8000) {
        *(unsigned char *)(*state + 0x1c7) = 9;
    } else {
        *(unsigned char *)(*state + 0x1c7) = 2;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
