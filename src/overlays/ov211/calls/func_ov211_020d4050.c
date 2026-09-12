typedef struct { int x, y, z; } Vec3;

extern void func_ov211_020d5e1c(int a, int b, int c);
extern long long func_01ff8a14(int num, int denom);
extern void func_ov107_020c5c54(int obj, void *v);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov211_020d415c(void);

void func_ov211_020d4050(int *self) {
    int *state = (int *)self[1];
    int leaderVal;
    long long q;
    int delta;
    Vec3 v;

    if (*(unsigned char *)((char *)state + 0x64) == 0) {
        leaderVal = *(int *)(*(int *)(*(int *)(*state + 0x3d4)) + 0x194);
        func_ov211_020d5e1c(leaderVal, 0, 0);
        *(unsigned char *)((char *)state + 0x64) = 1;
    }
    state[0xb] += *(int *)(self[0] + 0x2c);
    state[0xc] += *(int *)(self[0] + 0x2c);
    q = func_01ff8a14(state[0xc], 0x555);
    if (q > 0x100000000LL) {
        q = 0x100000000LL;
    }
    delta = (int)(((q * (long long)0x1666) + 0x80000000LL) >> 32);
    v = *(Vec3 *)(state + 0xd);
    v.y = v.y + (delta - 0x1000);
    func_ov107_020c5c54(state[0], &v);
    if (q == 0x100000000LL) {
        state[0xb] = 0;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)func_ov211_020d415c);
    }
}
