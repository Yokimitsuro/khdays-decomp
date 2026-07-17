/* Per-frame spin + drift step (x4: ov127/128/129/130). Advance the spin angle by dt
 * (0203d040 with the rate at ctx[10]), turn it into a rotation and compose it onto the
 * owner's orientation at +0xa0. Then publish last frame's drift (ctx+0x18) to the owner's
 * +0xf0 and clear it. Finally, only while the hw60 lo bit 0 is set and the current move is
 * one of 2/4/5/6, accumulate dt into the lifetime at ctx+0x3c and queue move 7 once it
 * reaches 0x8000.
 *
 * Case order from tools/switchorder.py: {2,4,5,6} share one body and {0,1,3} share the
 * default's, i.e. only the first group is written.
 *
 * Two spellings are load-bearing, both about WHERE a value is materialised:
 *  - `ctx[9] = func_0203d040(...)` then passing `ctx[9]` on. Routing it through a local
 *    (`r = f(); ctx[9] = r; g(..., r)`) makes mwcc copy into r2 first and store the COPY,
 *    where the ROM stores r0 straight out of the call and copies afterwards.
 *  - the drift pointer must be a local scoped to the copy block. Declared in the prologue
 *    it gets hoisted into a callee-saved register (+1 in the push list); left fully inline
 *    it lands in the other scratch than the ROM's. It is used twice (ldm then stm) while
 *    the destination is used once -- the ROM gives lr to the two-use value. */
struct vec3 { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };

extern int func_0203d040(int a, int b, int c, void *d);
extern void func_0202f188(void *out, void *a, int b);
extern void func_0202ed60(void *out, void *a, void *b);
extern void func_0202ef54(void *out, void *a, void *b);
extern void func_0203c9d0(void *a, void *b);
extern struct vec3 data_02041dc8;
extern int data_02042264[];

void func_ov130_020ccb10(int *self, int p2, int p3, int p4) {
    int *ctx = (int *)self[1];
    int q[4];
    int m[4];
    int t;

    ctx[9] = func_0203d040(ctx[9], ctx[10], *(int *)(self[0] + 0x2c), 0);
    func_0202f188(q, data_02042264, ctx[9]);
    func_0202ed60(m, data_02042264, (void *)(*ctx + 0x124));
    func_0202ef54(m, m, q);
    func_0203c9d0((void *)(*ctx + 0xa0), m);
    { struct vec3 *v = (struct vec3 *)(ctx + 6);
    *(struct vec3 *)(*ctx + 0xf0) = *v;
    *v = data_02041dc8; }
    if ((((struct hw60 *)(*ctx + 0x60))->lo & 1) == 0) {
        return;
    }
    switch (*(signed char *)(*ctx + 0x1c6)) {
    case 2:
    case 4:
    case 5:
    case 6:
        t = ctx[0xf] + *(int *)(self[0] + 0x2c);
        ctx[0xf] = t;
        if (t >= 0x8000) {
            *(char *)(*ctx + 0x1c7) = 7;
        }
        break;
    }
}
