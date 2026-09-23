/* Leap tick of the ov210 enemy (x3 with ov211/ov282). Once (+0x64) the height of the +0x3d4
 * part's first node (+0x194) is handed to ov210 3ffc. The target is re-acquired into +0x10 --
 * none requests sub-state 2 and ends the action. Until the +0x66 byte marks it, the +0x60 timer
 * accumulates the owner's rate and past 0x199 fires reaction 0x117 mode 5 at the +4 point. The
 * +0x28 heading faces the target's +0x190 from the +4 point. The +0x2c timer accumulates the rate
 * and, while positive, the +0x30 timer's fraction of 0x4cc (capped at 1.0) raises the +0x34 base
 * by up to 1.0 and the owner is announced there (ov107 c5c54). Once the +0xc idle byte clears,
 * sub-state 8 is requested and the action ends. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov211_020d5e1c(int height, int a, int b);
extern int func_ov107_020cab14(int owner, int flag);
extern int func_ov107_020c5af8(int a, int b, int c, int d);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern long long func_01ff8a14(int num, int denom);
extern void func_ov107_020c5c54(int obj, void *v);
extern void func_0203c634(int self, int idx, int cb);

void func_ov211_020d375c(int *self) {
    int *state = (int *)self[1];
    Vec3 d;
    Vec3 v;
    long long q;

    if (*(unsigned char *)((char *)state + 0x64) == 0) {
        func_ov211_020d5e1c(*(int *)(**(int **)(state[0] + 0x3d4) + 0x194), 0, 0);
        *(unsigned char *)((char *)state + 0x64) = 1;
    }
    state[4] = func_ov107_020cab14(state[0], 0);
    if (state[4] == 0) {
        *(char *)(state[0] + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    if (*(unsigned char *)((char *)state + 0x66) == 0) {
        state[0x18] += *(int *)(*self + 0x2c);
        if (state[0x18] >= 0x199) {
            *(unsigned char *)((char *)state + 0x66) = 1;
            func_ov107_020c5af8(state[0], 0x117, 5, state[1]);
        }
    }
    VEC_Subtract((void *)(state[4] + 0x190), (void *)state[1], &d);
    state[0xa] = func_020050b4(d.x, d.z);
    state[0xb] += *(int *)(*self + 0x2c);
    if (state[0xb] > 0) {
        state[0xc] += *(int *)(*self + 0x2c);
        q = func_01ff8a14(state[0xc], 0x4cc);
        if (q > 0x100000000LL) {
            q = 0x100000000LL;
        }
        v = *(Vec3 *)(state + 0xd);
        v.y += (int)(((q * (long long)0x1000) + 0x80000000LL) >> 32);
        func_ov107_020c5c54(state[0], &v);
    }
    if (*(unsigned char *)state[3] == 0) {
        *(char *)(state[0] + 0x1c7) = 8;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
    }
}
