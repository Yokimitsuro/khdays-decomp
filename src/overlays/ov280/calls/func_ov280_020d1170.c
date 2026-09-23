/* func_ov280_020d1170 -- chase tick of the ov280 enemy. The +0x18
 * heading turns towards the +0x1c target heading (8x the owner's rate when +0x4a is 1, else 3x)
 * and orients the owner's +0xa0 pose. Without a target (+0x14, re-acquired by
 * func_ov280_020d0628) sub-state 2 is requested and the tick ends. The +0x24 delay runs down in
 * sub-states 2/4. In those sub-states a 7.0 floor probe (func_ov280_020d0750) is cast; with a
 * target 7.0 or more below the +8 point sub-state 0xe is requested (unless +0x58 is set), and one
 * 3.0 or more above arms the +0x2c climb timer (0xd00). When the probe hits, the climb timer raises
 * the +0x34 lift by 0x200 per tick while it runs down, and the distance from the +0xc point to the
 * contact raises it below 1.07 or lowers it above 2.67 (once the climb is over). Finally the +0x30
 * velocity goes to the owner's +0xf0 and is scaled by 0.25. */
typedef struct { int x, y, z; } Vec3;

extern int func_0203d040(int from, int to, int step, int mode);
extern void func_0202f188(void *q, const Vec3 *axis, int angle);
extern void func_0203c9d0(void *pose, void *q);
extern void func_ov280_020d0628(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_ov280_020d0750(int *node, Vec3 *dir, int direct);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern const Vec3 data_02042264;
extern const Vec3 data_ov280_020d3698;

void func_ov280_020d1170(int *node)
{
    int *state = (int *)node[1];
    int q[4];
    Vec3 probe;
    int len;
    int d;

    state[6] = func_0203d040(state[6], state[7],
                             *((unsigned char *)state + 0x4a) != 1 ? *(int *)(*node + 0x2c) * 3 : *(int *)(*node + 0x2c) << 3, 0);
    func_0202f188(q, &data_02042264, state[6]);
    func_0203c9d0((void *)(*state + 0xa0), q);
    if (state[5] == 0) {
        func_ov280_020d0628(node);
        if (state[5] == 0) {
            *(unsigned char *)(*state + 0x1c7) = 2;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    if (state[9] > 0) {
        if (*(signed char *)(*state + 0x100 + 0xc6) == 2 || *(signed char *)(*state + 0x100 + 0xc6) == 4) {
            state[9] -= *(int *)(*node + 0x2c);
        }
        if (state[9] < 0) {
            state[9] = 0;
        }
    }
    if (*(signed char *)(*state + 0x100 + 0xc6) == 2 || *(signed char *)(*state + 0x100 + 0xc6) == 4) {
        probe = data_ov280_020d3698;
        probe.y = func_ov280_020d0750(node, &probe, 1);
        if (state[5] != 0) {
            d = *(int *)(state[2] + 4) - *(int *)(state[5] + 0x194);
            if (d >= 0x7000) {
                if (state[0x16] == 0) {
                    *(unsigned char *)(*state + 0x1c7) = 0xe;
                }
            } else if (*(int *)(state[5] + 0x194) - *(int *)(state[2] + 4) >= 0x3000) {
                state[0xb] = 0xd00;
            }
        }
        if (probe.y != 0) {
            VEC_Add(&probe, (Vec3 *)state[3], &probe);
            VEC_Subtract(&probe, (Vec3 *)state[3], &probe);
            len = func_01ff8d18(&probe, &probe);
            if (state[0xb] != 0) {
                state[0xd] += 0x200;
                state[0xb] -= *(int *)(*node + 0x2c);
                if (state[0xb] < 0) {
                    state[0xb] = 0;
                }
            }
            if (len < 0x2908) {
                state[0xd] += 0x200;
            } else if (len > 0x6694) {
                if (state[0xb] == 0) {
                    state[0xd] -= 0x200;
                }
            }
        }
    }
    {
        Vec3 *vel = (Vec3 *)(state + 0xc);
        *(Vec3 *)(*state + 0xf0) = *vel;
        func_01ffa724(0x400, vel, vel);
    }
}
