struct hw60 { unsigned short lo:8, hi:8; };

extern void func_0203c634(void *node, int slot, void *cb);
extern void VEC_Add(void *a, void *b, void *out);
extern void func_01ffa724(int scale, void *src, void *dst);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int VEC_Mag(void *v);
extern void func_01ff8d18(void *src, void *dst);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov182_020cf8c8(void);
extern short data_0203d210[];

void func_ov182_020cf664(int *param_1) {
    int *state = (int *)param_1[1];
    *(int *)(*state + 0x394) = 1;
    if (state[4] == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(param_1, *(signed char *)(param_1 + 8), 0);
        return;
    }
    {
        int angle = (int)(((unsigned)(((long long)state[0x13] * 0x28be60db9391LL
                     + 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
        int local_28[3];
        int s34[3];
        int l40[3];
        int t, t2, t3, t2x3, mag;
        local_28[1] = state[0x11];
        local_28[0] = data_0203d210[angle * 2] << 1;
        local_28[2] = data_0203d210[angle * 2 + 1] << 1;
        VEC_Add(local_28, (void *)(state[4] + 400), local_28);
        t = state[7] + *(int *)(*param_1 + 0x2c);
        t2 = (int)(((long long)t * t + 0x800) >> 12);
        t3 = (int)(((long long)t2 * t + 0x800) >> 12);
        state[7] = t;
        t2x3 = 3 * t2;
        func_01ffa724(2 * t3 - t2x3 + 0x1000, state + 0x10, s34);
        {
            int h01 = -2 * t3;
            h01 += t2x3;
            func_01ffa724(h01, local_28, l40);
        }
        VEC_Add(s34, l40, s34);
        func_01ffa724(t + (t3 - 2 * t2), state + 10, l40);
        VEC_Add(s34, l40, s34);
        func_01ffa724(t3 - t2, state + 0xd, l40);
        VEC_Add(s34, l40, s34);
        VEC_Subtract(s34, (void *)state[1], state + 0x15);
        state[0x16] = 0;
        mag = VEC_Mag(state + 0x15);
        if (mag > 0x800) {
            func_01ff8d18(state + 0x15, state + 0x15);
            func_01ffa724(0x800, state + 0x15, state + 0x15);
        }
        VEC_Subtract((void *)(state[4] + 400), (void *)state[1], l40);
        state[6] = func_020050b4(l40[0], l40[2]);
        if (state[7] >= 0x1000) {
            func_ov107_020c9264(*state, 7, 0);
            ((struct hw60 *)(*state + 0x60))->hi &= ~2;
            state[7] = 0;
            func_0203c634(param_1, *(signed char *)(param_1 + 8), func_ov182_020cf8c8);
        }
    }
}
