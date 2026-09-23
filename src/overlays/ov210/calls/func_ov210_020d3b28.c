/* Rise tick of the ov210 enemy (x3 with ov211/ov282). Until the +0x66 byte marks it, the +0x60
 * timer accumulates the owner's rate and past 0x999 fires reaction 0x117 mode 4 at the +4 point.
 * The +0x2c timer accumulates the rate; past 0xaaa the +0x30 timer's fraction of 0x888 (capped at
 * 1.0) lifts the +0x34 base down by up to 6.0 and the owner is announced there (ov107 c5c54).
 * Once the +0xc idle byte clears, sub-state 0x12 is requested and the action ends. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020c5af8(int a, int b, int c, int d);
extern long long func_01ff8a14(int num, int denom);
extern void func_ov107_020c5c54(int obj, void *v);
extern void func_0203c634(int self, int idx, int cb);

void func_ov210_020d3b28(int *self) {
    int *state = (int *)self[1];
    long long q;
    Vec3 v;

    if (*(unsigned char *)((char *)state + 0x66) == 0) {
        state[0x18] += *(int *)(*self + 0x2c);
        if (state[0x18] >= 0x999) {
            *(unsigned char *)((char *)state + 0x66) = 1;
            func_ov107_020c5af8(state[0], 0x117, 4, state[1]);
        }
    }
    state[0xb] += *(int *)(*self + 0x2c);
    if (state[0xb] > 0xaaa) {
        state[0xc] += *(int *)(*self + 0x2c);
        q = func_01ff8a14(state[0xc], 0x888);
        if (q > 0x100000000LL) {
            q = 0x100000000LL;
        }
        v = *(Vec3 *)(state + 0xd);
        v.y -= (int)(((q * (long long)0x6000) + 0x80000000LL) >> 32);
        func_ov107_020c5c54(state[0], &v);
    }
    if (*(unsigned char *)state[3] == 0) {
        *(char *)(state[0] + 0x1c7) = 0x12;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
    }
}
