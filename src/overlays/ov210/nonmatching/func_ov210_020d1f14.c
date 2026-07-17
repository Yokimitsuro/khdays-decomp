/*
 * NONMATCHING -- 192/192 size-exact, diff @0x29: a symmetric r6/r7 swap between `target` and `owner`
 * (=*state). SOLVED (keep it): caching `*state` in the `owner` local forces mwcc to hold BOTH values
 * in callee-saved regs across FX_Sqrt, which fixes the push list ({r3..r7,lr}) and homes `out` in the
 * r3 push slot instead of a `sub sp,#4` -- that was the original 16-byte gap. What remains is only
 * which of the two gets r6 vs r7 (ROM: target=r7 owner=r6; mwcc: reversed). Everything else is
 * byte-exact. Attack only the target/owner register choice.
 *
 * func_ov210_020d1f14 -- x3 (ov210/211/282). AI-state tick: if the target is far enough, commit to a
 * charge; otherwise set a random wait and idle.
 * If the sub-node byte *(u8)state[3] is set, keep waiting. Acquire the target (020cab14, distance^2
 * out-param) -> state[4]. If found and FX_Sqrt(dist2) - target[0x80] - owner[0x80] >= 0xa000, mark
 * *state+0x1c7 = 5 and bail. Otherwise pick a random wait state[0x1b] = lo + RandNextScaled(abs(hi-lo)
 * +1) (lo/hi at *state+0x224/+0x228), mark *state+0x1c7 = 2 and bail. (0203c634 cb=0 either way.)
 */
extern int  func_ov107_020cab14(int obj, void *out);
extern int  FX_Sqrt(int x);
extern int  func_02023eb4(int mul);
extern void func_0203c634(int self, int idx, int cb);

void func_ov210_020d1f14(int *self) {
    int *state = (int *)self[1];
    int out;
    int target;

    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    target = func_ov107_020cab14(*state, &out);
    state[4] = target;
    if (target != 0) {
        int *owner = (int *)*state;
        out = FX_Sqrt(out) - *(int *)(target + 0x80) - owner[0x20];
        if (out >= 0xa000) {
            *(char *)(*state + 0x1c7) = 5;
            func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
            return;
        }
    }
    {
        int lo = *(int *)(*state + 0x224);
        int d = *(int *)(*state + 0x228) - lo;
        state[0x1b] = lo + func_02023eb4((d < 0 ? -d : d) + 1);
    }
    *(char *)(*state + 0x1c7) = 2;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
