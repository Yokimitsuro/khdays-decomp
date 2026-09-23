/* Decision tick of an ov235 state: the +0x40 timer clears and the +0x5c path point is resolved
 * (func_ov235_020cccc0) into the +0x10 step. Once the +0xc idle byte clears a d101 picks the next
 * sub-state -- 0xc below 40, 9 below 80, else 2 -- and the tick ends. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov235_020cccc0(int *state, int point, Vec3 *dir, int *speed);
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

void func_ov235_020ce4f8(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;
    int roll;

    state[0x10] = 0;
    func_ov235_020cccc0(state, state[0x17], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    roll = RandRange(0, 100);
    if (roll < 0x28) {
        *(unsigned char *)(*state + 0x1c7) = 0xc;
    } else if (roll < 0x50) {
        *(unsigned char *)(*state + 0x1c7) = 9;
    } else {
        *(unsigned char *)(*state + 0x1c7) = 2;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
