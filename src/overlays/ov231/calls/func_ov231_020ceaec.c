/* func_ov231_020ceaec -- the sweep tick: advance the swept point, test it against the world, and
 * score a hit. Entered from func_ov231_020ce9d0, hands off to func_ov231_020cec2c.
 *
 * Past 0x5000 on ctx[8] the tracked point is refreshed (func_ov231_020cc9e0). The point at
 * ctx+0x3c is copied to ctx+0x30 and pushed through func_01ffa724 with 0xb80 -- note that first
 * argument is a plain literal here, so it is an id/amount, not a matrix pointer.
 *
 * The test is a 32-byte query built on the stack: the previous point (from *ctx[3]), the current
 * one (ctx+0x3c) and the two limits 0x2000 / 0x1000. On a hit the score at +0x1c goes up by
 * 0x3244 (which mwcc splits into +0x244 and +0x3000 -- it is not an encodable immediate) and
 * effect 0x51 fires.
 *
 * The state holds until the gate at *ctx[4] reads 0, EXCEPT that a hit forces the hand-off
 * immediately regardless of the gate.
 *
 * data_02041dc8 is a 12-byte vector passed BY VALUE; the `sub r3,sp,#8` straddles it across sp so
 * two words land in r2/r3 and the third is already in the outgoing stack slot. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    VecFx32 from;
    VecFx32 to;
    int limitA;
    int limitB;
} SweepQuery;

extern void func_ov231_020cc9e0(int self);
extern void func_01ffa724(int amount, VecFx32 *v, VecFx32 *out);
extern int func_ov231_020ccc48(int self, int a, SweepQuery *q, VecFx32 *pt, int n);
extern void func_ov107_020c5af8(int owner, int a, int b, int ptr);
extern void func_ov107_020c0b90(int owner, int effect, VecFx32 v, int a);
extern void func_ov231_020cd094(int self, int a, int b, int c, void (*cb)(void));
extern void func_ov231_020cec2c(void);
extern VecFx32 data_02041dc8;

void func_ov231_020ceaec(int self) {
    int *ctx;
    SweepQuery q;
    int hit;

    ctx = *(int **)(self + 4);
    hit = 0;
    if (ctx[8] > 0x5000) {
        func_ov231_020cc9e0(self);
    }

    ctx[0xa] += *(int *)(*(int *)self + 0x2c);
    *(VecFx32 *)((char *)ctx + 0x30) = *(VecFx32 *)((char *)ctx + 0x3c);
    func_01ffa724(0xb80, (VecFx32 *)((char *)ctx + 0x30), (VecFx32 *)((char *)ctx + 0x30));

    q.from = *(VecFx32 *)ctx[3];
    q.to = *(VecFx32 *)((char *)ctx + 0x3c);
    q.limitA = 0x2000;
    q.limitB = 0x1000;
    if (func_ov231_020ccc48(self, 0, &q, (VecFx32 *)((char *)ctx + 0x3c), 3) != 0) {
        ctx[7] += 0x3244;
        func_ov107_020c5af8(ctx[0], 0, 0x51, ctx[0] + 0x74);
        hit = 1;
    }

    if (*(unsigned char *)ctx[4] != 0 && hit == 0) {
        return;
    }

    func_ov107_020c0b90(ctx[0], 7, data_02041dc8, 0);
    func_ov231_020cd094(self, 0xb, 0xb, 0, func_ov231_020cec2c);
}
