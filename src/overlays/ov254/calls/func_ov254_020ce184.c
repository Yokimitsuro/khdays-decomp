/* Update of the ov254 actor (+0x30): the +0x30 heading turns towards +0x34 (020d040) at half the
 * frame rate in moves 2, 4 and 0xb, the full rate in move 7 and 1.0 / 1.5 x in move 5 (rider /
 * free, +0x80), and orients the +0xa0 pose. In moves 2 and 4 a free actor's +0x3c grip runs down;
 * the +0x4d8 cooldown always does. The +0x10 climb follows the next route point (020cd840) by
 * 1/32 of the height difference in moves 2 and 7; in move 4 (not frozen, +0x7c) it keeps the
 * +0x60 extra lift (rider) or burns it off; the other flying moves keep their climb and the rest
 * zero it. The velocity goes to the actor's +0xf0 with x / z cleared and +0x24 takes the +8
 * track position. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;

extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0203c9d0(int a, void *b);
extern int func_ov254_020cd840(int *state, int a);
extern const Vec3 data_02042264;

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov254_020ce184(int *node)
{
    int *state = (int *)node[1];
    Quat q;
    int rate = 0;

    switch (*(signed char *)(*state + 0x100 + 0xc6)) {
    case 2:
    case 4:
    case 0xb:
        rate = FX_Mul(*(int *)(node[0] + 0x2c), 0x800);
        break;
    case 5:
        rate = FX_Mul(*(int *)(node[0] + 0x2c), state[0x20] != 0 ? 0x1000 : 0x1800);
        break;
    case 7:
        rate = FX_Mul(*(int *)(node[0] + 0x2c), 0x1000);
        break;
    }
    state[0xc] = func_0203d040(state[0xc], state[0xd], rate, 0);
    func_0202f188(&q, &data_02042264, state[0xc]);
    func_0203c9d0(*state + 0xa0, &q);
    if ((*(signed char *)(*state + 0x100 + 0xc6) == 2 || *(signed char *)(*state + 0x100 + 0xc6) == 4) &&
        state[0x1e] == 0) {
        state[0xf] -= *(int *)(node[0] + 0x2c);
        if (state[0xf] <= 0) {
            state[0xf] = 0;
        }
    }
    *(int *)((char *)*state + 0x4d8) -= *(int *)(node[0] + 0x2c);
    if (*(int *)((char *)*state + 0x4d8) <= 0) {
        *(int *)((char *)*state + 0x4d8) = 0;
    }
    switch (*(signed char *)(*state + 0x100 + 0xc6)) {
    case 4:
        if (state[0x1f] != 0) {
            break;
        }
        state[4] = func_ov254_020cd840(state, -1) - *(int *)(state[2] + 4);
        if (state[0x1e] != 0) {
            state[4] = FX_Mul(state[4] + state[0x18], 0x80);
        } else if (state[4] >= 0 && state[0x18] >= state[4]) {
            state[0x18] = 0;
        } else {
            state[4] = state[0x18] + FX_Mul(state[4], 0x80);
        }
        break;
    case 2:
    case 7:
        state[4] = FX_Mul(func_ov254_020cd840(state, -1) - *(int *)(state[2] + 4), 0x80);
        break;
    case 5:
    case 6:
    case 8:
    case 0xa:
    case 0xb:
        break;
    default:
        state[4] = 0;
        break;
    }
    *(Vec3 *)(*state + 0xf0) = *(Vec3 *)(state + 3);
    state[3] = state[5] = 0;
    *(Vec3 *)(state + 9) = *(Vec3 *)state[2];
}
