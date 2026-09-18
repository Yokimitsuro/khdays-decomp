/* Charge 0x1bbb of the ov156 enemy (and its byte-identical twin): re-acquires the target into
 * +0x18 and aims the +0x14 heading at it; the +0x30 rate is the frame delta * 30 / 10 and the
 * +0x2c timer accumulates the delta. Once past 0x1bbb the telegraph (cc9c4) fires once (+0x38)
 * and, while the timer is within [0x1bbb, 0x22a9], the ground sweep eases in over 0x6ee.
 * When the +4 sub-node goes idle: bit 0 of the +0x38c item's +8 byte clears, the +0x1c shot
 * counter is rolled (1..3), animation 5 plays, the heading is re-aimed at the target with a
 * random spread (RandNextScaled(0x1923) - 0xc91), the timer and flags reset (bit 1 of +0x39)
 * and the state advances to cdbd4. */
struct b8 { unsigned int b : 8; };
extern int func_ov107_020cab14(int obj, int out);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_020050b4(int x, int z);
extern void func_ov157_020ce7e4(int *state, int *p);
extern long long func_01ff8a14(int a, int b);
extern void func_ov157_020ce8c8(int *state, int lo, int hi, int *p);
extern int func_02023eb4(int mul);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int self, int idx, int cb);
extern int func_ov157_020cf9f4;
void func_ov157_020cf820(int *self) {
    int *state = (int *)self[1];
    int aim[3];
    int aim2[3];
    int t;
    state[6] = func_ov107_020cab14(*state, 0);
    if (state[6] != 0) {
        VEC_Subtract((void *)(state[6] + 0x190), (void *)state[2], aim);
        state[5] = func_020050b4(aim[0], aim[2]);
        state[0xc] = *(int *)(*self + 0x2c) * 0x1e / 10;
    }
    state[0xb] += *(int *)(*self + 0x2c);
    if (*(unsigned char *)(state + 0xe) == 0 && state[0xb] >= 0x1bbb) {
        func_ov157_020ce7e4(state, state + 8);
        *(unsigned char *)(state + 0xe) = 1;
    }
    t = state[0xb];
    if (t >= 0x1bbb && t <= 0x22a9) {
        long long fx = func_01ff8a14(t - 0x1bbb, 0x6ee);
        func_ov157_020ce8c8(state, (int)fx, (int)((unsigned long long)fx >> 32), state + 8);
    }
    if (*(unsigned char *)state[1] != 0) {
        return;
    }
    ((struct b8 *)(*(int *)(*state + 0x38c) + 8))->b &= ~1;
    state[7] = func_02023eb4(3) + 1;
    func_ov107_020c9264(*state, 5, 0);
    if (state[6] != 0) {
        VEC_Subtract((void *)(state[6] + 0x190), (void *)state[2], aim2);
        {
            int roll = func_02023eb4(0x1923) - 0xc91;
            int a = func_020050b4(aim2[0], aim2[2]);
            a += roll;
            state[5] = a;
        }
    }
    state[0xb] = 0;
    *(unsigned char *)(state + 0xe) = 0;
    *(unsigned char *)((int)state + 0x39) &= ~2;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov157_020cf9f4);
}
