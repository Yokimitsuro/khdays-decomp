/* func_ov137_020cd2d8 -- start the move: set the countdown, then lay down a scaled ground-plane
 * direction from the stored heading and hand off to the per-frame step (func_ov137_020cd414).
 *
 * The countdown at +0x14 is `(*self)[0x2c] * 30 / 10` -- kept unfolded rather than simplified to
 * `* 3`, because that is the multiply-then-magic-divide the ROM emits.
 *
 * Once the progress counter at +0x40 reaches 0x200 the move is over and nothing else happens.
 *
 * The heading at +0xc is Q12 RADIANS; see codegen-cracks.md ("Q12 radians -> 16-bit angle ->
 * sin/cos table"). data_0203d210 is sin/cos interleaved, so [idx*2] is the sine and [idx*2+1] the
 * cosine. The conversion is written out TWICE on purpose: the ROM recomputes it for each
 * component rather than reusing the index, and hoisting it into one local loses the match.
 *
 * Both components are scaled by FX_Mul(., 0x300) -- 0.1875 in Q12 -- and land as a 4-word vector
 * at +0x30: {sin*0.1875, 0x400, cos*0.1875, 0}. FX_Mul is inlined by the ROM (there is no FX_
 * reloc), which is why it is a static inline here; -inline on,noauto only inlines what is marked.
 *
 * ------------------------------------------------------------------------------------------
 * NONMATCHING: 316/316 bytes. Every value, constant and store is right; the ONLY difference is
 * instruction scheduling at 0xbc, and it is worth spelling out because this family has 7 members.
 *
 *   ROM:  ldr r8,[r4,#0xc] ; mov r6,#0 ; umull sl,sb,r8,r3 ; mla sb,r8,ip,sb ; asr r7,r8,#0x1f
 *   mine: ldr r8,[r4,#0xc] ; mov r6,#0 ; asr r7,r8,#0x1f ; mov r0,r5 ; ldr r2,[pc] ; umull ...
 *
 * mwcc hoists the two c634 argument-setup instructions (`mov r0,r5` and the pool load of the
 * callback) ~12 instructions early, to fill the load-use stall between `ldr r8,[r4,#0xc]` and the
 * `umull` that consumes it. The ROM just eats the stall and sets those arguments up immediately
 * before the `bl`. Both spend the same 316 bytes.
 *
 * Why it matches in the FIRST conversion block but not the second: at the first, r0 and r2 are
 * still live (r0 holds 0x400 pending its store, r2 holds the sine), so the scheduler has nowhere
 * to put the hoist. By the second block both are free and it takes the opportunity. That makes
 * this the known arg-setup-order / scheduling tie class, not something the C can steer: no
 * ordering of the statements changes which registers are free at that point.
 *
 * Retried 2026-07-20 after a run of parks that turned out to be untested axes rather
 * than ties.  This one held.  Additionally ruled out, all still 0xbc:
 *   - hoisting the 0 and the 0x400 into locals declared before the conversions (the
 *     lever that fixed the 96-byte Tally family, and the ROM's own early `mov r6,#0`
 *     made it look promising);
 *   - a second index local for the second conversion, and an `action` local for the
 *     c634 argument;
 *   - a local for the callback pointer (+4 bytes, worse);
 *   - propagating c634's return value out of this function, i.e. checklist item 5.
 *     Several externs in the tree declare func_0203c634 as returning int, so this was
 *     a real candidate; it costs 4 bytes and does not move 0xbc.
 * Arity of func_0203c634 re-confirmed as 3 from matched call sites.
 *
 * Everything else here is confirmed and reusable -- the maths is byte-exact (it is the same
 * conversion that matched outright in func_ov228_020d01e8). Retry only under a different mwcc
 * build; do not re-derive the constants or re-litigate the double conversion. */

extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_0203c634(int self, int action, void (*cb)(void));
extern void func_ov137_020cd414(void);
extern short data_0203d210[];

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov137_020cd2d8(int self) {
    int *ctx;
    int idx;

    ctx = *(int **)(self + 4);
    ctx[5] = *(int *)(*(int *)self + 0x2c) * 30 / 10;
    if (ctx[0x10] >= 0x200) {
        return;
    }

    func_ov107_020c9264(ctx[0], 2, 0);

    idx = (unsigned short)(((long long)ctx[3] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    ctx[0xc] = FX_Mul(data_0203d210[idx * 2], 0x300);
    ctx[0xd] = 0x400;

    idx = (unsigned short)(((long long)ctx[3] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    ctx[0xe] = FX_Mul(data_0203d210[idx * 2 + 1], 0x300);
    ctx[0xf] = 0;

    func_0203c634(self, *(signed char *)(self + 0x20), func_ov137_020cd414);
}
