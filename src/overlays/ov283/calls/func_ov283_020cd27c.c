/* Walk tick of the ov283 actor: after the shared step (020ccb48, target distance) the +0x48 walk
 * timer runs down. Past the +0x50 limit (0x7f80) the next move is 9. When the timer runs out the next
 * move is picked: beyond 15.0 move 8, beyond 6.0 move 6 (or 10 on a d100 roll up to 10); closer the
 * +0x34 reroll (1.57 to 3.14) is taken and the ground ahead of the turned-around +0x40 heading is
 * probed (radius 0x100, range +0x80): with a clear floor the actor faces the target (+0x38 / +0x40)
 * and dashes (5), else move 4 (+0x7c = the roll passed 2.36, +0x3c cleared). While walking within
 * twice the +0x80 range a one-time (+0x78) d100 roll over 70 makes the next move 7. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov283_020ccb48(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_02023eb4(int bound);
extern int func_02023e80(int bound);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_01fff8e8(int collision, Vec3 *origin, Vec3 *dir, int radius, void *ignore);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov283_020cd27c(int *node)
{
    int *state = (int *)node[1];
    Vec3 out;
    Vec3 dir;
    int dist;
    int lo = 0;

    dist = func_ov283_020ccb48(node);
    state[0x12] -= *(int *)(node[0] + 0x2c);
    if (state[0x14] > 0x7f80) {
        *(signed char *)(*state + 0x1c7) = 9;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0x12] <= 0) {
        if (dist > 0xf000) {
            *(signed char *)(*state + 0x1c7) = 8;
        } else if (dist > 0x6000) {
            if (func_02023eb4(0x65) + lo > 10) {
                *(signed char *)(*state + 0x1c7) = 6;
            } else {
                *(signed char *)(*state + 0x1c7) = 10;
            }
        } else {
            int world = *(int *)(*state + 4);
            int hit;

            state[0xd] = func_02023e80(0x1922) + 0x1922;
            {
                int idx = ANG2IDX(state[0x10] + 0x3244) * 2;

                dir.x = data_0203d210[idx];
                dir.y = 0;
                dir.z = data_0203d210[idx + 1];
            }
            func_01ffa724(*(int *)(*state + 0x80), &dir, &out);
            hit = func_01fff8e8(*(int *)(world + 0x7c), (Vec3 *)(*state + 0x74), &out, 0x100, 0);
            if (hit != 0 && *(int *)(hit + 8) == 0) {
                {
                    int idx = ANG2IDX(state[0xe]) * 2;

                    dir.x = data_0203d210[idx];
                    dir.y = 0;
                    dir.z = data_0203d210[idx + 1];
                }
                VEC_Subtract((Vec3 *)(*(int *)(*state + 0x390) + 0x74), (Vec3 *)(*state + 0x74), &out);
                func_01ff8d18(&out, &out);
                state[0xe] = state[0x10] = func_020050b4(out.x, out.z);
                *(signed char *)(*state + 0x1c7) = 5;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            state[0x1f] = state[0xd] > 0x25b3;
            state[0xf] = 0;
            *(signed char *)(*state + 0x1c7) = 4;
        }
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (dist > *(int *)(*state + 0x80) * 2) {
        return;
    }
    if (state[0x1e] != 0) {
        return;
    }
    if (func_02023eb4(0x65) + lo > 0x46) {
        *(signed char *)(*state + 0x1c7) = 7;
    }
    state[0x1e] = 1;
}
