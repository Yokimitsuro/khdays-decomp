/* func_ov245_020cd1d0 -- boss motion tick: turns the actor's +0xa0 placement to the +0x24
 * heading (quaternion around data_02042264), takes the negated +0x4cc anchor direction as the
 * push and, in sub-states 4 / 7 / 8 / 9 (8 first resets the +0xc velocity to (0, 0, -1/64)),
 * zeroes the velocity while the push has length. Sub-states 4 / 5 run the +0x2c timer down;
 * +0x4c4 marks sub-states 2 / 4 / 9 / 10 as moving. The push joins the velocity and the frame's
 * step is scaled from it. While the actor is live (bit 0 of +0x60) its +0x3bc query block moved
 * by the step lets every live, flagged actor of the scene's +0xa8 list with a +0x18c rider re-seat
 * that rider's +0x20 child at its +0xa8 point clamped between -24.0 and the query top (minus the
 * actor's +0x80 radius), briefly detached (020ad8e0). The +8 anchor is then kept between the
 * -11.0 (or -9.0 in sub-state 10) floor and the +0x3c height plus 15.0 (020c5c54), otherwise the
 * two +0x4d0 wave phases advance by the step over 0.83 / 0.75 x pi (wrapped at pi) and the
 * velocity, with x and y cleared, is copied to +0xf0. Finally the velocity is zeroed and, once the
 * +0x34 delay runs out, every idle +0x420 part is launched along data_0204227c (020cf230).
 * Codegen: compiled with opt_dead_assignments and opt_strength_reduction off (push/pop scoped);
 * the phase slot is addressed as `*state + j * 4 + 0x4d0` before the call, as in the ROM. */
typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };
struct Flags40 { int bit0 : 1, bit1 : 1; };
struct Ov245Query { Vec3 pos; Vec3 a; Vec3 b; Vec3 c; int w0; int w1; int w2; };
struct Ov245Actor { char pad[0x420]; int parts[3]; char pad42c[0x4d0 - 0x42c]; int phases[2]; };
struct Ov245Rider { char pad[0xa8]; Vec3 point; };
struct XY { int x, y; };

static inline void VecSet_(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

extern void func_0202f188(int *quat, const Vec3 *axis, int angle);
extern void func_0203c9d0(int placement, const int *quat);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list);
extern void func_ov022_020ad8e0(int target, int a);
extern void func_0202b450(int node, Vec3 *pos);
extern void func_ov107_020c5c54(int actor, Vec3 *pos);
extern int func_02020400(int num, int den);
extern void func_ov245_020cf230(int part, const Vec3 *dir);
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;
extern const Vec3 data_0204227c;

#pragma push
#pragma opt_dead_assignments off
#pragma opt_strength_reduction off
void func_ov245_020cd1d0(int *node) {
    int *state = (int *)node[1];
    int quat[4];
    Vec3 step;
    Vec3 back;
    Vec3 pos;
    struct Ov245Query query;
    Vec3 v;
    int moving2;
    int moving;
    int moving3;
    int actor;
    int kind;
    int sub;
    int scene;
    int *entry;
    int other;
    Vec3 *point;
    int limit;
    int sum;
    int *anchor;
    int j;
    int m;

    func_0202f188(quat, &data_02042264, state[9]);
    func_0203c9d0(*state + 0xa0, quat);
    func_01ffa724(-0x1000, (Vec3 *)(*(int *)(*state + 0x4cc) + 0x2c), &back);
    switch (*(signed char *)(*state + 0x1c6)) {
    case 8:
        state[3] = 0;
        state[4] = 0;
        state[5] = -0x40;
    case 4:
    case 7:
    case 9:
        if (func_01ff8d18(&back, &pos) != 0) {
            *(Vec3 *)(state + 3) = data_02041dc8;
        }
        break;
    }
    if (!(*(signed char *)(*state + 0x1c6) != 4 && *(signed char *)(*state + 0x1c6) != 5)) {
        state[0xb] -= *(int *)(node[0] + 0x2c);
        if (state[0xb] < 0) {
            state[0xb] = 0;
        }
    }
    actor = *state;
    moving3 = 1;
    moving = 1;
    moving2 = 1;
    kind = *(signed char *)(actor + 0x1c6);
    if (kind != 2 && kind != 4) {
        moving = 0;
    }
    if (moving == 0) {
        if (kind != 10) {
            moving2 = 0;
        }
    }
    if (moving2 == 0) {
        if (kind != 9) {
            moving3 = 0;
        }
    }
    *(int *)(actor + 0x4c4) = moving3;
    VEC_Add((Vec3 *)(state + 3), &back, (Vec3 *)(state + 3));
    func_01ffa724((*(int *)(node[0] + 0x2c) << 12) / 0x88, (Vec3 *)(state + 3), &step);
    if ((((struct hw60 *)(*state + 0x60))->lo & 1) != 0) {
        scene = *(int *)(*state + 4);
        query = *(struct Ov245Query *)(*state + 0x3bc);
        VEC_Add(&query.pos, &step, &query.pos);
        entry = func_01fffd70((void *)(scene + 0xa8));
        other = entry == 0 ? 0 : *entry;
        while (other != 0) {
            if (((struct Flags40 *)(other + 0x40))->bit1 && (((struct hw60 *)(other + 0x60))->lo & 1) != 0 &&
                (sub = *(int *)(other + 0x18c)) != 0) {
                point = &((struct Ov245Rider *)*(int *)(sub + 0x20))->point;
                if (point != 0) {
                    v = *point;
                    limit = (query.pos.z - query.w2) - *(int *)(other + 0x80);
                    if (v.z > limit) {
                        v.z = limit;
                    } else if (v.z < -0x18000) {
                        v.z = -0x18000;
                    } else {
                        goto next;
                    }
                    func_ov022_020ad8e0(sub, 1);
                    func_0202b450(*(int *)(sub + 0x20), &v);
                    func_ov022_020ad8e0(sub, 0);
                }
            }
        next:
            entry = func_01fffd8c((void *)(scene + 0xa8));
            other = entry == 0 ? 0 : *entry;
        }
    }
    anchor = (int *)state[2];
    limit = (*(signed char *)(*state + 0x1c6) == 10 ? 0x2000 : 0) - 0xb000;
    sum = anchor[2] + step.z;
    if (sum < limit) {
        VecSet_(&pos, anchor[0], anchor[1], limit);
        func_ov107_020c5c54(*state, &pos);
    } else if (sum > state[0xf] + 0xf000) {
        VecSet_(&pos, anchor[0], anchor[1], state[0xf] + 0xf000);
        func_ov107_020c5c54(*state, &pos);
    } else {
        for (j = 0; j < 2; j++) {
            int amp = j == 0 ? 0x3500 : 0x3000;
            int *phase = (int *)(*state + j * 4 + 0x4d0);

            *phase += func_02020400(step.z * 0x6488, (int)(((long long)amp * (0x6488 >> 1) + 0x800) >> 12));
            while (((struct Ov245Actor *)*state)->phases[j] >= 0x3244) {
                ((struct Ov245Actor *)*state)->phases[j] -= 0x3244 * 2;
            }
        }
        state[4] = 0;
        state[3] = 0;
        *(Vec3 *)(*state + 0xf0) = *(Vec3 *)(state + 3);
    }
    *(Vec3 *)(state + 3) = data_02041dc8;
    if (state[0xd] <= 0) {
        return;
    }
    state[0xd] -= *(int *)(node[0] + 0x2c);
    if (state[0xd] > 0) {
        return;
    }
    state[0xd] = 0;
    for (m = 0; m < 3; m++) {
        if ((((struct hw60 *)(((struct Ov245Actor *)*state)->parts[m] + 0x60))->lo & 1) == 0) {
            func_ov245_020cf230(((struct Ov245Actor *)*state)->parts[m], &data_0204227c);
        }
    }
}
#pragma pop
