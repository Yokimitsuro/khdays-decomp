/* Attack tick of the ov299 enemy: once the +0x24 timer reaches the +0x2c delay, the +4 target
 * position is taken; with a +8 target actor it is instead that actor's +0x190 position offset
 * by a random direction (yaw within +-0x3244 of straight ahead) at a random distance of
 * +-0x100, +-0x1800 or +-0x3000 (30/30/40 % rolls). The point is raised 0x14000 and the number
 * of 0x60-accelerating fall steps that cover 0x14000 is counted; the +0xc velocity becomes the
 * facing (sin, 0, cos) of the +0x28 yaw at 0x800 and the point is pulled back by that many
 * steps along it before c5c4 launches the actor there; d47dc takes over. */
typedef struct Vec3 { int x, y, z; } Vec3;

extern int func_02023eb4(int range);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void VEC_Add(const void *a, const Vec3 *b, Vec3 *d);
extern void func_ov107_020c5c54(int actor, Vec3 *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov299_020d47dc(int *node);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + func_02023eb4(span + 1);
}

void func_ov299_020d45d4(int *node)
{
    int *state = (int *)node[1];
    Vec3 target;
    Vec3 dir;
    int speed;
    int ang;
    int roll;
    unsigned int idx;
    int y;
    int v;
    int n;

    state[9] += *(int *)(*node + 0x2c);
    if (state[9] < state[0xb]) {
        return;
    }
    target = *(Vec3 *)state[1];
    if (state[2] != 0) {
        ang = func_02023eb4(0x6489) - 0x3244;
        roll = func_02023eb4(100);
        if (roll < 30) {
            speed = 0x100;
        } else if (roll < 60) {
            speed = 0x1800;
        } else {
            speed = 0x3000;
        }
        idx = ANG2IDX(ang);
        dir.x = data_0203d210[idx * 2];                                       /* FX_SinIdx */
        dir.y = 0;
        dir.z = data_0203d210[idx * 2 + 1];                                   /* FX_CosIdx */
        func_01ffa724(RandRange(-speed, speed), &dir, &dir);
        VEC_Add((void *)(state[2] + 0x190), &dir, &target);
    }
    target.y += 0x14000;
    y = 0;
    v = 0;
    n = 0;
    do {
        y += v;
        v += 0x60;
        n++;
    } while (y < 0x14000);
    idx = ANG2IDX(state[0xa]);
    state[3] = data_0203d210[idx * 2];                                        /* FX_SinIdx */
    state[4] = 0;
    state[5] = data_0203d210[idx * 2 + 1];                                    /* FX_CosIdx */
    func_01ffa724(0x800, (Vec3 *)(state + 3), (Vec3 *)(state + 3));
    target.x -= state[3] * n;
    target.z -= state[5] * n;
    func_ov107_020c5c54(*state, &target);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov299_020d47dc);
}
