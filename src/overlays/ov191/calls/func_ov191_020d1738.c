/* Leap tick of the ov191 enemy (x3: ov191/192/193): re-acquires the target (020d1bdc) and, if
 * any, faces its +0x190 anchor from the +8 position and sets the turn rate (+0x30) to 30x the
 * node's +0x2c speed over 10; the +0x2c phase advances by that speed. At 0x1bbb the ground
 * below the model is probed once (+0x38 latch) into the +0x20 landing point, and between 0x1bbb
 * and 0x22a9 the descent is driven (020d073c) with the 64-bit fraction (phase - 0x1bbb) /
 * (0x1bbb / 4). Once the actor's first byte says the pose is over: bit 0 of the +0x38c item's +8
 * is dropped, the +0x1c counter re-rolled to 2 + rand(5), pose 5 plays, the heading is
 * re-aimed at the target with a random +-0xc90 spread, the phase and latch reset, bit 1 of
 * +0x39 cleared and the follow-up handler (020d190c) installed. */
typedef struct { int x, y, z; } Vec3;
struct bf { unsigned b : 8; };

extern int func_ov191_020d1bdc(int obj, int *out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_ov191_020d0658(int *node, Vec3 *out);
extern long long func_01ff8a14(int num, int denom);
extern void func_ov191_020d073c(int *node, long long t, Vec3 *at);
extern int func_02023eb4(int bound);
extern void func_ov107_020c9264(int obj, int anim, int flag);
extern void func_0203c634(int node, int slot, void *cb);
extern void func_ov191_020d190c(void);

void func_ov191_020d1738(int node)
{
    int *state = *(int **)(node + 4);
    Vec3 d;
    Vec3 d2;
    int spread;
    int heading;

    state[6] = func_ov191_020d1bdc(*state, 0);
    if (state[6] != 0) {
        VEC_Subtract((Vec3 *)(state[6] + 0x190), (Vec3 *)state[2], &d);
        state[5] = func_020050b4(d.x, d.z);
        state[0xc] = *(int *)(*(int *)node + 0x2c) * 30 / 10;
    }
    state[0xb] += *(int *)(*(int *)node + 0x2c);
    if (*(unsigned char *)(state + 0xe) == 0 && state[0xb] >= 0x1bbb) {
        func_ov191_020d0658(state, (Vec3 *)(state + 8));
        *(unsigned char *)(state + 0xe) = 1;
    }
    if (state[0xb] >= 0x1bbb && state[0xb] <= 0x22a9) {
        func_ov191_020d073c(state, func_01ff8a14(state[0xb] - 0x1bbb, 0x1bbb >> 2), (Vec3 *)(state + 8));
    }
    if (*(unsigned char *)state[1] != 0) {
        return;
    }
    ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b &= ~1;
    state[7] = func_02023eb4(5) + 2;
    func_ov107_020c9264(*state, 5, 0);
    if (state[6] != 0) {
        VEC_Subtract((Vec3 *)(state[6] + 0x190), (Vec3 *)state[2], &d2);
        spread = func_02023eb4(0x1923) - 0xc91;
        heading = func_020050b4(d2.x, d2.z);
        state[5] = heading + spread;
    }
    state[0xb] = 0;
    *(unsigned char *)(state + 0xe) = 0;
    *(unsigned char *)((char *)state + 0x39) &= ~2;
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov191_020d190c);
}
