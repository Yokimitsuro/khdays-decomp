/*
 * func_ov000_02057dc4 -- UNFINISHED, and it is ONE FRAME-LAYOUT PERMUTATION from done.
 * 824/824 bytes, 206/206 instructions. x7 family (ov004/005/008/009/025 + ov069)
 * -> WORTH 7 FUNCTIONS. This is the best-value open lead in the project right now.
 *
 * It is the row renderer called by RebuildViewAndCountCells (0205836c), which matched.
 *
 * WHAT IT DOES: walk the 8x5 grid of cells at `rowbase` (row stride 5 words). Skip empty
 * cells and cells already claimed by `mask` (a 64-bit set, bit = col + row*5). Claim the
 * rest into *out, then dispatch on the cell's kind (+0x18):
 *   0        -> 02056b18 with the cell's payload (+0x14)
 *   1        -> 02056bac for each of the 4 sub-slots that has one (+0x34, stride 8)
 *   3, 5, 6  -> 02056cb4 for the same 4 sub-slots, passing the two u16s at +0x38/+0x3a,
 *               then accumulate the signed byte stats at +0x2a..+0x2f and the word at
 *               +0x30 into self+0x78..+0x90
 *   2, 4     -> nothing
 * Then, for every kind, add the cell's 13 word stats (+0x54..+0x84) into self+0x94..+0xc4
 * and clamp all 14 of those to 0x64000.
 *
 * SOLVED, keep all of it:
 *  - `mask` is ONE `unsigned long long` parameter, not two uints: it arrives in the r2:r3
 *    pair and the caller loads it with `ldr r2,[r0,#0xcc] ; ldr r3,[r0,#0xd0]`. `out` is
 *    the 5th argument, on the stack at [sp,#0x48].
 *  - The clamp loop MUST use the fold `((int *)self)[i + 0x25]` (0x94/4 == 0x25). Spelling
 *    it `*(int *)(self + i*4 + 0x94)` strength-reduces into a walking pointer and is
 *    exactly the ONE instruction that stood between 828 and 824. (This is the
 *    dividing-offset case of the codegen-cracks.md entry -- 0x94 divides by 4, so here
 *    the fold is right; contrast 0205836c, where 0xcc does NOT divide by 8 and the struct
 *    member is right instead. Same rule, opposite branch.)
 *
 * THE DIFF: the four spilled scalars land in different stack slots.
 *      ROM:   0x10 = rowoff, 0x14 = col, 0x18 = row, 0x1c = rowp (compiler temp)
 *      mine:  0x14 = row,    0x1c = rowoff, 0x10 = rowbase copy, ...
 * Every instruction is otherwise identical, including the whole 64-bit shift dance, the
 * switch table, all 20 accumulations and the clamp loop. Only the [sp,#N] immediates and
 * the knock-on register choices differ.
 *
 * PRE-PARK CHECKLIST -- all four run:
 *  1. --thumb: ARM gives the exact 824/824.
 *  2. Arity: 02056b18 4 · 02056bac 5 · 02056cb4 5, all matching the ROM's register setup;
 *     this function's own 5 params confirmed from the caller (which matched byte-exact).
 *  3. No constant is in the wrong register.
 *  4. Diff read back: 206 vs 206, same opcodes, same order; only spill slots move.
 *
 * RULED OUT (11 spellings):
 *   5 declaration orders of row/col/rowoff/i -- byte-IDENTICAL output, so spill slots are
 *     NOT declaration-order driven (that rule is for AGGREGATES; these are scalars the
 *     allocator spills on its own terms). Worth recording: it is the first place the
 *     first-declared-highest rule has NOT applied.
 *   the loops as do-while with `row = 0` before `rowoff = 0` (Ghidra's shape, which lets
 *     mwcc copy the 0) -- both `row < 8` and `row <= 7`
 *   `rowp` as an explicit local -> 812 (3 SHORT): it stays in a register, where the ROM
 *     spills it to 0x1c. So the ROM has MORE pressure than my C creates.
 *   `rowp` as `&((int *)rowbase)[rowoff]` -> also 812
 *   mask as two uints with Ghidra's `||` hi/lo test -> 828
 *   the body nested in the negated test instead of two `continue`s -> 828
 *   `bit` hoisted into a local -> 828
 *
 * NEXT STEP -- and this is a good one: the `rowp`-as-a-local result (812) says the ROM's
 * frame has MORE live state than my C produces, which is probably also why its slots are
 * numbered differently. Find the source form that makes mwcc spill rowp WITHOUT losing
 * those 3 instructions, and the slot numbering will likely fall out with it. Do not grind
 * declaration order -- that axis is measured and dead here.
 */
extern void func_ov000_02056b18(int self, int a, int b, int c);
extern void func_ov000_02056bac(int self, int a, int b, int c, int d);
extern void func_ov000_02056cb4(int self, int a, unsigned int b, unsigned int c, int d);

void func_ov000_02057dc4(int self, int rowbase, unsigned long long mask, unsigned long long *out) {
    int row;
    int col;
    int rowoff;
    int i;

    rowoff = 0;
    for (row = 0; row < 8; row++) {
        for (col = 0; col < 5; col++) {
            int cell = *(int *)(rowbase + rowoff * 4 + col * 4);
            if (cell == 0) {
                continue;
            }
            if ((mask & (1ULL << (col + rowoff))) != 0) {
                continue;
            }
            *out |= 1ULL << (col + rowoff);
            switch (*(int *)(cell + 0x18)) {
            case 0:
                func_ov000_02056b18(self, *(int *)(cell + 0x14), 1, 0);
                break;
            case 1:
                for (i = 0; i < 4; i++) {
                    int e = cell + i * 8;
                    if (*(int *)(e + 0x34) != 0) {
                        func_ov000_02056bac(self, *(int *)(e + 0x34), 0, 1, 0);
                    }
                }
                break;
            case 3:
            case 5:
            case 6:
                for (i = 0; i < 4; i++) {
                    int e = cell + i * 8;
                    if (*(int *)(e + 0x34) != 0) {
                        func_ov000_02056cb4(self, *(int *)(e + 0x34),
                                            *(unsigned short *)(e + 0x38),
                                            *(unsigned short *)(e + 0x3a), 0);
                    }
                }
                *(int *)(self + 0x78) += *(unsigned char *)(cell + 0x2a);
                *(int *)(self + 0x7c) += *(signed char *)(cell + 0x2b);
                *(int *)(self + 0x80) += *(signed char *)(cell + 0x2c);
                *(int *)(self + 0x84) += *(signed char *)(cell + 0x2e);
                *(int *)(self + 0x88) += *(signed char *)(cell + 0x2d);
                *(int *)(self + 0x8c) += *(int *)(cell + 0x30);
                *(int *)(self + 0x90) += *(signed char *)(cell + 0x2f);
                break;
            }
            *(int *)(self + 0x94) += *(int *)(cell + 0x54);
            *(int *)(self + 0x98) += *(int *)(cell + 0x58);
            *(int *)(self + 0x9c) += *(int *)(cell + 0x5c);
            *(int *)(self + 0xa0) += *(int *)(cell + 0x60);
            *(int *)(self + 0xa4) += *(int *)(cell + 0x64);
            *(int *)(self + 0xa8) += *(int *)(cell + 0x68);
            *(int *)(self + 0xac) += *(int *)(cell + 0x6c);
            *(int *)(self + 0xb0) += *(int *)(cell + 0x70);
            *(int *)(self + 0xb4) += *(int *)(cell + 0x74);
            *(int *)(self + 0xb8) += *(int *)(cell + 0x78);
            *(int *)(self + 0xbc) += *(int *)(cell + 0x7c);
            *(int *)(self + 0xc0) += *(int *)(cell + 0x80);
            *(int *)(self + 0xc4) += *(int *)(cell + 0x84);
            for (i = 0; i < 0xe; i++) {
                if (((int *)self)[i + 0x25] > 0x64000) {
                    ((int *)self)[i + 0x25] = 0x64000;
                }
            }
        }
        rowoff += 5;
    }
}
