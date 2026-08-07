/*
 * Per-tick AI decision for the ov127 chaser.
 *
 * Speed falls with the actor's remaining hit points, so a hurt chaser closes
 * more slowly. It re-aims (the facing tick), turns the new heading into a
 * velocity through the shared sin/cos table, and runs down the move timer.
 * While the timer is live, or the owner is busy, nothing else happens.
 *
 * When it expires the chaser reconsiders by health band: above three quarters
 * it charges on a coin flip; between a half and three quarters it holds;
 * between a quarter and a half it rolls a d100 and either charges (under 20)
 * or backs off (under 60); below a quarter it always backs off. If nothing
 * requested a state, it notifies instead of taking a slot.
 */

struct Vecx32 { int x, y, z; };

static inline void VEC_Set(struct Vecx32 *vec, int x, int y, int z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

extern int func_02020400(int num, int den);
extern void func_ov127_020cc5b8(int *self);
extern void func_01ffa724(int scale, struct Vecx32 *v, struct Vecx32 *d);
extern int func_02023eb4(int range);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov107_020c9264(int actor, int a, int b);
extern const short data_0203d210[];

void func_ov127_020ccf5c(int *self)
{
    int *nd = (int *)self[1];
    int actor = *nd;
    int speed;
    int idx;
    int cap;
    int hp;
    int roll;
    int timer;
    struct Vecx32 *vel;

    if (*(short *)(actor + 0x218) == 0) {
        speed = 0;
    } else {
        speed = 0x580 - func_02020400(*(short *)(actor + 0x21a) * 0x380,
                                      *(short *)(actor + 0x218));
    }
    func_ov127_020cc5b8(self);

    idx = (int)(((unsigned)(((long long)(int)(unsigned)nd[9] * 0x28be60db9391LL +
                 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    vel = (struct Vecx32 *)(nd + 6);
    vel->x = (int)data_0203d210[idx * 2];
    vel->y = 0;
    vel->z = (int)data_0203d210[idx * 2 + 1];
    func_01ffa724(speed, vel, vel);

    timer = nd[0xe] - *(int *)(*self + 0x2c);
    nd[0xe] = timer;
    if (timer <= 0) {
        nd[0xe] = 0;
    }
    if (*(unsigned char *)(nd[1] + 0xad) != 0) {
        return;
    }
    if (nd[0xe] <= 0) {
        cap = *(short *)(actor + 0x218);
        hp = *(short *)(actor + 0x21a);
        if (hp >= cap * 0x4b / 100) {
            if (func_02023eb4(2) != 0) {
                *(char *)(*nd + 0x1c7) = 2;
            }
        } else if (hp < cap * 0x32 / 100) {
            if (hp >= cap * 0x19 / 100) {
                roll = func_02023eb4(100);
                if (roll < 0x14) {
                    *(char *)(*nd + 0x1c7) = 2;
                } else if (roll < 0x3c) {
                    *(char *)(*nd + 0x1c7) = 5;
                }
            } else {
                *(char *)(*nd + 0x1c7) = 5;
            }
        }
        if (*(signed char *)(*nd + 0x1c7) != -1) {
            func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
            return;
        }
    }
    func_ov107_020c9264(*nd, 2, 0);
}
