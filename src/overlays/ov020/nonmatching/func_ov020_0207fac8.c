/*
 * func_ov020_0207fac8 -- UNFINISHED. 60/60 bytes, 24/24 instructions.
 * ★ THUMB. Verify with --thumb.
 * ov020 is 3/11; this is its smallest stub, and the only thing wrong with it is which of two
 * SCRATCH registers the pointer lands in.
 *
 * WHAT IT DOES: resolve the two operands of the bytecode instruction (02021948 on the descriptor,
 * 02021980 on descriptor+4 words), hand them to 0206aeb8 with kind 0x11, then drop BG3 and BG1 to
 * priority 0. Returns 1 (the bytecode "handled, advance" convention shared by ov020's handlers).
 *
 * ★ THE POOL LITERAL IS MMIO, AND IT HAS NO RELOC. Ghidra prints `DAT_arm9_ov020__0207fb00` and
 * `puVar1[-2]`, which reads like two data symbols. There is no reloc at +0x38 -- the literal is
 * the value 0x0400000E, i.e. REG_BG3CNT, and `subs r1, r1, #4` walks it back to 0x0400000A =
 * REG_BG1CNT. This is exactly the pool-label trap in the skill: no reloc at the offset ⇒ it is a
 * literal, not a symbol. Written as a held volatile pointer per the project's MMIO convention;
 * two independent raw casts would need two pool entries and the ROM has one.
 *
 * MEASURED, worth keeping: the mask is `~3`, NOT `0xfffc`. They are the same value for a u16 and
 * they do NOT compile the same -- `&= 0xfffc` costs one instruction more (64 B), because mwcc
 * materialises the literal instead of reusing `movs r0,#3` + `bics`. Both `p[0]`/`p[-2]` and
 * `*p`/`p -= 2` spellings are byte-identical here, unlike in func_ov044_020b3634 where the index
 * form mattered -- so that crack is specific to predicated stores, not general.
 *
 * THE DIFF, all of it:
 *      ROM:   ldr r1,[pc] (p -> r1) ; ldrh r2,[r1] ... subs r1, r1, #4   (p mutated IN PLACE)
 *      mine:  ldr r2,[pc] (p -> r2) ; ldrh r1,[r2] ... subs r1, r2, #4   (p-2 gets a NEW reg)
 * p and the loaded temp are simply swapped. Both are caller-saved scratch, both are free (nothing
 * is live across the point), and both cost the same. 24 instructions either way.
 *
 * PRE-PARK CHECKLIST:
 *  1. --thumb: YES -- 60/60 in THUMB.
 *  2. Arity: 0206aeb8 had a `(void)` extern in the tree and NO C call site, so its prologue was
 *     read directly: THUMB, 104 B, `push {r3,r4,r5,r6,lr}` + `sub sp,#0x104`, consumes r0..r3,
 *     and its only [sp] access is `str r4,[sp]` -- an OUTGOING argument for a call it makes, not
 *     an incoming read. So FOUR args, which is what is written here. 02021948/02021980 both take
 *     2 and are used elsewhere in the tree.
 *  3. No constant is misplaced: `movs r0,#3` and `movs r3,#0x11` are in the ROM's registers.
 *  4. Diff read back: 24 vs 24, same opcodes, same order, two registers transposed.
 *
 * RULED OUT (11 spellings, none moved the diff off 0x23):
 *   `p -= 2` · `p = p - 2` · `p--; p--` · `*(p - 2)` · `p[0]`/`p[-2]` · p declared before the
 *   two calls · p declared after · the load/store temp made an explicit local (declared before p,
 *   after p, and as two separate locals) -- all byte-identical to each other.
 *
 * NEXT STEP: this is the fourth function this session whose residue is "identical instruction
 * shape, different register choice, identical cost" (with func_ov039_020b3570, and the parked
 * func_ov029_020b2ee0 and func_ov301_020cbfc4). In every one, the ROM reaches for the register
 * mwcc does not, and no C-level lever moves it. That is worth treating as a CLASS rather than
 * four coincidences -- see deferred-ties.md. Do not spend more single-function effort here; if
 * the class has a cause, it will be found by comparing the four, not by a twelfth spelling of
 * this one.
 */
extern int func_02021948(int owner, unsigned short *desc);
extern int func_02021980(int owner, unsigned short *desc);
extern void func_ov002_0206aeb8(int a, int b, int c, int d);

int func_ov020_0207fac8(int owner, unsigned short *desc) {
    int a = func_02021948(owner, desc);
    int b = func_02021980(owner, desc + 4);
    volatile unsigned short *p = (volatile unsigned short *)0x400000e;

    func_ov002_0206aeb8(a, b, 0, 0x11);
    *p &= ~3;
    p -= 2;
    *p &= ~3;
    return 1;
}
