/* Roll the next attack and commit to it (x3: ov212/266/267) -- the callback armed by
 * Ov212_ReleaseSubObjectsAndAdvance. Bail unless bit 0 of the hw60 lo byte is set.
 * Otherwise latch the owner's cached angle (+0x584) into both the current and target
 * slots, clear the two counters, and pick the wind-up delay uniformly from the
 * inclusive range [owner+0x224, owner+0x228] -- the ROM takes abs() of the span so the
 * bounds may be stored either way round. Copy the owner's move id (+0x1b0), let
 * 020cd5d8 configure it, and unless the chosen slot is already 1, release sub-object 0
 * and re-kick it. Finally publish the slot at owner+0x1c7 and advance with no callback.
 *
 * `lo + func_02023eb4(d + 1)` in one expression is what produces the ROM's `add r0,r6,r0`
 * AFTER the bl (lo held in a callee-saved register across the call). */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned f : 8; };

extern int func_02023eb4(int a);
extern void func_ov267_020d11e8(int *ctx);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *self, int idx, void *cb);

void func_ov267_020d265c(void *self) {
    int *ctx = *(int **)((char *)self + 4);
    int v;
    int lo, hi, d;

    if ((((struct hw60 *)(*ctx + 0x60))->lo & 1) == 0) {
        return;
    }
    v = *(int *)(*ctx + 0x584);
    ctx[0xf] = v;
    ctx[0xd] = v;
    ctx[0x1a] = 0;
    ctx[3] = 0;
    lo = *(int *)(*ctx + 0x224);
    hi = *(int *)(*ctx + 0x228);
    d = hi - lo;
    if (d < 0) {
        d = -d;
    }
    ctx[0x13] = lo + func_02023eb4(d + 1);
    *(unsigned short *)((char *)ctx + 0x58) = *(unsigned short *)(*ctx + 0x1b0);
    func_ov267_020d11e8(ctx);
    if (*(signed char *)(*ctx + 0x1c9) != 1) {
        ctx[0x1b] = 0;
        ((struct b8 *)(((int *)*ctx)[0x133] + 8))->f &= ~2;
        func_ov107_020c9264(*ctx, 4, 1);
    }
    *(char *)(*ctx + 0x1c7) = *(signed char *)(*ctx + 0x1c9);
    func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
}
