/* Hover tick of the ov221 enemy. Airborne outside sub-state 6 the +0x50 heading turns towards
 * +0x58 at 0x96 (0x28 without a +0x78 target) per 100 of rate (0203d040), and the owner's
 * +0xa0 pose takes the heading about data_02042264. Sub-state 6 drains the +0x68 timer. The
 * +0x14 step is copied out and, in sub-states 2/4/5/6 with a target, its y becomes half the
 * gap from the +8 point to the target's +0x194 plus 2.0 (less whatever the owner's +0x13c
 * exceeds 9.0 by, never below the target itself), clamped to [-0x100, 0x60]; in sub-state 9 a
 * cast of the owner's +0x80 radius along the step from its +0x74 clips the step to the first
 * blocking hit. The step lands in the owner's +0xf0 and the +0x14 velocity decays by 0x300 per
 * 0x88 of rate. A +0x60 bit-0 owner then runs the jump handler (ov221 1044) and, once it has
 * launched (+0x400 bit 7), accumulates +0x41c up to 0xc38: within it the strike sweep (ov221
 * 0a2c mode 6) runs from the +0x410 landing with the three axes and a reach growing from 0x1933
 * to 0x4333 across the window. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int q[4]; } Quat;

struct Ov221SweepParams {
    Vec3 aim;
    Vec3 v0c;
    Vec3 v18;
    Vec3 v24;
    int nReach;
    int bFlag;
};

struct CollisionHit {
    int pad00;
    int pad04;
    int nBlocked;
    int nAlong;
};

struct b1 { unsigned char b0 : 1; };
struct hw60 { unsigned short lo : 8, hi : 8; };

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern int func_0203d040(int cur, int target, int step, int flag);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0203c9d0(void *pose, Quat *q);
extern int func_ov107_020cab14(int owner, int flag);
extern struct CollisionHit *func_01fff8e8(void *collision, Vec3 *origin, Vec3 *dir, int radius, void *ignore);
extern void func_01ffd144(int scale, Vec3 *in, Vec3 *out);
extern int FX_Inv(int num, int den);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov223_020d0f58(int self, int *node);
extern void func_ov223_020d09cc(int *state, int mode, struct Ov221SweepParams *params);
extern const Vec3 data_02042264;
extern const Vec3 data_02042270;
extern const Vec3 data_02042258;

void func_ov223_020d170c(int *node)
{
    int *state = (int *)node[1];
    Quat q;
    Vec3 step;
    Vec3 origin;
    struct Ov221SweepParams params;
    int rem;
    int nStep;
    int target;
    int h;
    int d;
    int t;
    struct CollisionHit *hit;

    step = *(Vec3 *)(state + 5);
    if (((struct b1 *)(*state + 0x17a))->b0 == 0 && *(signed char *)(*state + 0x1c6) != 6) {
        state[0x14] = func_0203d040(state[0x14], state[0x16],
                                    *(int *)(*node + 0x2c) * (state[0x1e] != 0 ? 0x96 : 0x28) / 100, 0);
    }
    func_0202f188(&q, &data_02042264, state[0x14]);
    func_0203c9d0((void *)(*state + 0xa0), &q);
    if (*(signed char *)(*state + 0x1c6) == 6) {
        state[0x1a] -= *(int *)(*node + 0x2c);
        if (state[0x1a] < 0) {
            state[0x1a] = 0;
        }
    }
    switch (*(signed char *)(*state + 0x1c6)) {
    case 2:
    case 4:
    case 5:
    case 6:
        if (state[0x1e] != 0 && (target = func_ov107_020cab14(*state, 0)) != 0) {
            h = *(int *)(target + 0x194) + 0x2000;
            if (*(int *)(*state + 0x13c) > 0x9000) {
                h -= *(int *)(*state + 0x13c) - 0x9000;
            }
            if (h < *(int *)(target + 0x194)) {
                h = *(int *)(target + 0x194);
            }
            d = (h - *(int *)(state[2] + 4)) / 2;
            step.y = d;
            if (d > 0x60) {
                d = 0x60;
            } else if (d < -0x100) {
                d = -0x100;
            }
            step.y = d;
        }
        break;
    case 9:
        origin = *(Vec3 *)(*state + 0x74);
        hit = func_01fff8e8(*(void **)(*(int *)(*state + 4) + 0x7c), &origin, &step, *(int *)(*state + 0x80), 0);
        if (hit != 0 && hit->nBlocked == 0) {
            func_01ffd144(hit->nAlong, &step, &step);
        }
        break;
    }
    *(Vec3 *)(*state + 0xf0) = step;
    for (rem = *(int *)(*node + 0x2c); rem > 0; rem -= 0x88) {
        nStep = rem <= 0x88 ? rem : 0x88;
        func_01ffa724(0x1000 - FX_Mul(FX_Inv(nStep, 0x88), 0x300), (Vec3 *)(state + 5), (Vec3 *)(state + 5));
    }
    if ((((struct hw60 *)(*state + 0x60))->lo & 1) == 0) {
        return;
    }
    func_ov223_020d0f58(*state, node);
    if ((*(u8 *)(*state + 0x400) & 0x80) == 0) {
        return;
    }
    *(int *)(*state + 0x41c) += *(int *)(*node + 0x2c);
    if (*(int *)(*state + 0x41c) > 0xc38) {
        return;
    }
    params.aim = *(Vec3 *)(*state + 0x410);
    t = *(int *)(*state + 0x41c);
    if (t > 0xc38) {
        t = 0xc38;
    } else if (t < 0) {
        t = 0;
    }
    params.nReach = 0x2500 + (t * 0x3e00 / 0xc38 + 0x33);
    params.v0c = data_02042270;
    params.v18 = data_02042258;
    params.v24 = data_02042264;
    params.bFlag = 1;
    func_ov223_020d09cc(state, 6, &params);
}
