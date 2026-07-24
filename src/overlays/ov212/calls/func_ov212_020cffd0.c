/*
 * Acquire a target and face it. Ask ov107_020cab14 for one and cache it at ctx+0x5a8;
 * with none, latch phase 2 and dispatch. Otherwise measure the vector from the anchor
 * (ctx[2]) to the target (target+0x190), build the unit facing {sin, 0, cos} from the
 * STORED heading (ctx[0xd]) into ctx+0x28, scale it by 0x800, kick animation 0xd, clear
 * the phase timer and the two one-shot bytes, and chain to the next state.
 *
 * Two faithful game quirks, preserved on purpose:
 *  - The freshly measured atan2 (func_020050b4(d.x, d.z)) is COMPUTED AND DISCARDED; the
 *    facing is rebuilt from the stored heading instead. Same shape as ov231_020cdd3c's
 *    discarded VEC_DotProduct -- a likely original bug, reproduced, not fixed.
 *  - `0x800` does double duty: the Q12 rounding constant for the angle conversion and the
 *    first argument to func_01ffa724; mwcc CSEs it, so it is a single materialization.
 *
 * The match turns on `const short data_0203d210[]`: without const, mwcc must assume the
 * stores through ctx could alias the table, so it pins the second table load after the
 * two stores (permuted schedule, still 292 B). const is the aliasing fact that lets both
 * table loads issue before the stores. One of a 3-member family (ov266/ov267).
 */
struct vec3 { int x, y, z; };

extern int *func_ov107_020cab14(int a, int b);
extern int VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int a, int b);
extern void func_01ffa724(int s, struct vec3 *v, struct vec3 *out);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *self, int idx, void *cb);
extern void func_ov212_020d00f4(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov212_020cffd0(void *self) {
    int *ctx = *(int **)((char *)self + 4);
    struct vec3 d;
    unsigned int idx;
    int tgt;

    *(int *)(*ctx + 0x5a8) = (int)func_ov107_020cab14(*ctx, 0);
    tgt = *(int *)(*ctx + 0x5a8);
    if (tgt == 0) {
        *(char *)(*ctx + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
        return;
    }
    VEC_Subtract((char *)tgt + 0x190, (void *)ctx[2], &d);
    func_020050b4(d.x, d.z);
    idx = ANG2IDX(ctx[0xd]);
    ctx[0xa] = data_0203d210[idx * 2];
    ctx[0xb] = 0;
    ctx[0xc] = data_0203d210[idx * 2 + 1];
    func_01ffa724(0x800, (struct vec3 *)(ctx + 0xa), (struct vec3 *)(ctx + 0xa));
    func_ov107_020c9264(*ctx, 0xd, 0);
    ctx[0x10] = 0;
    *(char *)((char *)ctx + 0x5a) = 0;
    *(char *)((char *)ctx + 0x5b) = 0;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), func_ov212_020d00f4);
}
