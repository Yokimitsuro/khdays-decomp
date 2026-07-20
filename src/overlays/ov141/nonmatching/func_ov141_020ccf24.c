/* func_ov141_020ccf24 -- acquire a target and pick a randomised approach heading.
 *
 * NONMATCHING: 412/412 bytes, and the difference is SEVEN INSTRUCTIONS of scratch-register
 * naming inside one inlined 64-bit multiply.  Everything before and after is byte-identical.
 * Head of a 5-member family (ov141/142/143/149/150 and company), so it is worth finishing.
 *
 * SEMANTICS -- fully decoded, and none of it needs re-deriving.  The arithmetic is the same
 * idiom as func_ov137_020cc9e0, which IS matched and carries the long explanation; read that
 * file first.  The short version:
 *
 *   Ask the manager for a target (func_ov107_020cab14).  With none, set mode 2 in the owner's
 *   byte at 0x1c7 and end the state with no successor.
 *
 *   Otherwise take the flattened vector from ctx[0x10] to the target's position (target+0x74),
 *   normalise it, and measure `gap` = that length minus both collision radii (+0x80 each).
 *   Turn gap into a Q12 ratio -- against a CONSTANT 0xf000 here, where the ov137 twin reads
 *   the owner's reach from +0x2d8 and only falls back to 0xf000 when it is unset:
 *
 *       t = clamp(FX_Inv(gap, 0xf000) * 2 - 0x1000, -0x1000, 0x1000)
 *
 *   so t sweeps -1.0 .. +1.0 as the target goes from touching to a full reach away.  The
 *   scatter is then widest at mid-range and collapses at either extreme:
 *
 *       spread = 0x1000 - |t|
 *       off    = FX_Mul(rand(|spread * 2| + 1) - spread, PI)
 *
 *   t > 0 measures the REVERSED vector and subtracts the offset, t <= 0 measures it forwards
 *   and adds; both add PI (0x3244), which mwcc splits into +0x244 / +0x3000 because it is not
 *   an encodable ARM immediate.  The resulting Q12 radian is stored raw at ctx[3] -- unlike the
 *   ov137 twin, this one does NOT convert it to a table index or emit a direction vector.
 *
 *   Then arm the timer at ctx[4] = template->+0x2c * 30 / 5 (magic 0x66666667, asr #1 -- note
 *   /5, where the neighbouring handlers use /10 and /20), notify the owner with mode 1, clear
 *   the byte at ctx+0x48 and dispatch func_ov141_020cd0c0.
 *
 * ALREADY SOLVED, do not redo:
 *  - the RNG copy artifact.  The ROM emits `add r0, r0, #0` right after the rand call and the
 *    function is 4 bytes SHORT without it; `+ (t - t)` on the rand result produces it.  (The
 *    choice of variable does not matter -- spread, t and gap all work.)  Note this is the
 *    opposite situation to func_ov147_020cd3cc, where a `+ (v - v)` term was scaffolding that
 *    had to be REMOVED; there the ROM had no such instruction.  Check the disassembly for the
 *    `add rN, rN, #0` before adding or deleting one of these.
 *  - `ldm r5, {r1, r2}` is not a struct copy: it is mwcc fusing the adjacent reads of ctx[0]
 *    and ctx[1] for the two radii.  Writing them as two ordinary loads is correct and produces
 *    it; the ov137 twin reads ctx[2] and ctx[0], which are not adjacent, and gets two ldrs.
 *  - the divisor really is 5, verified against the pool literal, not the /10 of its siblings.
 *
 * THE DIFF, in full -- the ROM puts the rand-minus-spread difference in a FRESH register and
 * lets the inlined multiply use r4/r3, we reuse the dying r4 and shift everything down:
 *      ROM   sub r2, r0, r4 ; asr r1, r2, #0x1f ; umull r4, r3, r2, r0 ; adds r2, r4, #0x800
 *      ours  sub r4, r0, r4 ; asr r1, r4, #0x1f ; umull r3, r2, r4, r0 ; adds r3, r3, #0x800
 * and three more of the same through the mla/adc/lsr.  The final result lands in r4 in both.
 *
 * RULED OUT for that (nine spellings, every one still exactly 18 differing lines at 0xd1):
 *  - a named `delta` local for the difference instead of nesting it in the FX_Mul call;
 *  - the RNG artifact written against three different variables;
 *  - the multiply spelled inline rather than through the static-inline helper;
 *  - operands swapped in the helper, `(long long)b * a`;
 *  - a named `long long prod` intermediate, splitting the multiply from the shift;
 *  - reusing ONE variable for both `spread` and `off`, so the register cannot be recycled --
 *    this was the most promising idea and it changes nothing;
 *  - hoisting 0x3244 into a local (the hoisted-constant lever that cracked two families today);
 *  - dropping the rounding parenthesisation; making the multiplier unsigned.
 *
 * So the scratch choice inside the multiply is stable against every spelling of the multiply
 * itself AND against the live range of its input.  That points at something outside this
 * expression -- pressure from the two atan2 branches that follow, most likely -- which is the
 * direction to look, rather than another pass over the multiply.
 */
typedef struct { int x, y, z; } VecFx32;

extern int func_ov107_020cab14(int owner, int *out);
extern void func_0203c634(int *self, int action, void *cb);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern int func_01ff8d18(const VecFx32 *v, VecFx32 *unit);
extern int FX_Inv(int num, int den);
extern int func_02023eb4();
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_ov141_020cd0c0(void);

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov141_020ccf24(int *self) {
    int *ctx = (int *)self[1];
    VecFx32 v;
    int gap;
    int t;
    int spread;
    int off;

    ctx[1] = func_ov107_020cab14(ctx[0], 0);
    if (ctx[1] == 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
        return;
    }

    VEC_Subtract((const VecFx32 *)(ctx[1] + 0x74), (const VecFx32 *)ctx[0x10], &v);
    v.y = 0;
    gap = func_01ff8d18(&v, &v);
    gap = gap - *(int *)(ctx[1] + 0x80) - *(int *)(ctx[0] + 0x80);

    t = FX_Inv(gap, 0xf000) * 2 - 0x1000;
    if (t < -0x1000) {
        t = -0x1000;
    }
    if (t > 0x1000) {
        t = 0x1000;
    }

    spread = 0x1000 - (t < 0 ? -t : t);
    off = spread * 2;
    if (off < 0) {
        off = -off;
    }
    off = FX_Mul(func_02023eb4(off + 1) + (t - t) - spread, 0x3244);

    if (t > 0) {
        ctx[3] = (func_020050b4(-v.x, -v.z) + 0x3244) - off;
    } else {
        ctx[3] = off + (func_020050b4(v.x, v.z) + 0x3244);
    }

    ctx[4] = *(int *)(self[0] + 0x2c) * 0x1e / 5;
    func_ov107_020c9264(ctx[0], 1, 1);
    *((char *)ctx + 0x48) = 0;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), &func_ov141_020cd0c0);
}
