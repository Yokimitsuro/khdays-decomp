/* func_ov033_020b43dc -- fire the recoil burst: build a launch descriptor aimed opposite
 * the node's facing and submit it, then run the follow-up hit unless the actor is flagged.
 *
 * NONMATCHING: 332/332 bytes, and every instruction matches.  The whole residue is 27 lines
 * of REGISTER NAMING -- r1/r2/r3/r5/ip/lr permuted through the sin/cos block and the
 * descriptor fill.  Same opcodes, same operands, same order.
 *
 * SEMANTICS: only acts when the mode word at +0x7b0 is 0x9000.  Seeds a 0x2c-byte block
 * from func_ov022_020ad44c, then aims it: the node's angle at +0x80 minus half a turn,
 * shifted into the sin/cos table, with BOTH components NEGATED -- so the burst travels
 * away from where the node faces.  Speed 0x3000, the actor's short at +0x66 as the vertical
 * term, 0x1000 in the tail slot.  A second 0x28-byte argument block is filled around
 * func_ov022_020a23a4 and both go to func_ov022_020a0fb8; if that reports success and the
 * flags at +0x26bc have neither bit 0 nor bit 6, the follow-up at +0x26c8 runs with (0xca, 2).
 *
 * SOLVED, do not redo:
 *  - the stack layout is args at sp+0 (0x28) and blk at sp+0x28 (0x2c), so `blk` must be
 *    declared FIRST -- mwcc gives the lower address to the later declaration.
 *  - the byte at args+0x25 loses bits 0 and 1 through an `unsigned char` INTERMEDIATE:
 *    `v = b & ~1; b = v & ~2;`.  That intermediate is what produces the ROM's
 *    `and r0, r0, #0xff` between the two bics.  A `struct { unsigned char b : 8; }` bitfield
 *    overshoots by 28 bytes; folding the two clears into `& ~3` loses the pair entirely.
 *  - the descriptor stores are in the order written below.  Two other orders were measured:
 *    zeroing blk+0x18 first (to materialise 0 before 0x3000, as the ROM does) is 32 lines,
 *    and plain ascending offset order is 44.
 *
 * RULED OUT for the permutation: `register` on the index (the lever that closed ov301,
 * whose residue was also pure register choice), and hoisting data_0203d210 into a local
 * pointer both plain and `register` -- the last two are much worse, 53 lines, because the
 * table address then gets its own register instead of being rematerialised.
 *
 * PAIRS TRIED TOO, per the ov007 lesson from the same day (that function needed two changes
 * at once, each of which scored worse alone).  All four combinations of the three axes that
 * moved anything -- zero-first store order, `register` on the index, the table hoisted to a
 * local -- and none beats the 27 of the plain form: 32, 56, 53, 56.  So the pairs door is
 * closed here as well, which is worth knowing before someone spends a session on it.
 *
 * This is the callee-saved-permutation class, and the axes are exhausted at the single and
 * double level.  What has NOT been tried is a different mwcc build (tools/build_sweep.py);
 * given the C is instruction-perfect, that is now the cheapest remaining test.
 */
extern void func_ov022_020ad44c(void *out, char *self);
extern int func_ov022_020a23a4(char *self, int kind, void *a, void *b);
extern int func_ov022_020a0fb8(char *self, void *a, void *b);
extern void func_ov022_020ad28c(char *self, char *p, int a, int b);
extern const short data_0203d210[];

void func_ov033_020b43dc(char *self) {
    char blk[0x2c];
    char args[0x28];
    int idx;

    if (*(int *)(self + 0x7b0) != 0x9000) {
        return;
    }

    func_ov022_020ad44c(blk, self);

    idx = (unsigned short)(*(unsigned short *)(*(int *)(self + 0x20) + 0x80) - 0x8000) >> 4;
    *(int *)(blk + 0xc) = 0x3000;
    *(int *)(blk + 0x14) = -data_0203d210[idx * 2];
    *(int *)(blk + 0x1c) = -data_0203d210[idx * 2 + 1];
    *(int *)(blk + 0x18) = 0;
    *(int *)(blk + 0x10) = *(short *)(self + 0x66);
    *(int *)(blk + 0x20) = 0x1000;
    *(int *)(blk + 0x24) = 0;
    *(int *)(blk + 0x28) = 0;

    func_ov022_020a23a4(self, 0x2080, args, args + 4);

    *(int *)(args + 8) = 0x205;
    *(int *)(args + 0x18) = 0x66;
    {
        unsigned char v = *(unsigned char *)(args + 0x25) & ~1;
        *(unsigned char *)(args + 0x25) = v & ~2;
    }
    *(int *)(args + 0xc) = 0;
    *(int *)(args + 0x14) = 0xa00;
    *(int *)(args + 0x1c) = 0xa00;
    *(int *)(args + 0x20) = 0;
    *(unsigned char *)(args + 0x10) = 0;

    if (func_ov022_020a0fb8(self, blk, args) == 0) {
        return;
    }
    if ((*(int *)(self + 0x2000 + 0x6bc) & 1) != 0) {
        return;
    }
    if ((*(int *)(self + 0x2000 + 0x6bc) & 0x40) != 0) {
        return;
    }
    func_ov022_020ad28c(self, self + 0x2c8 + 0x2400, 0xca, 2);
}
