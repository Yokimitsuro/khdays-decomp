/*
 * func_ov294_020d1f94 -- UNFINISHED. 120 vs 116: ONE instruction over.
 * x3 family (ov295_020d3db4 / ov296_020d5bd4) -> worth 3, and ov294/295/296 are each
 * 11/14, so this is one of the three functions standing between them and 100%.
 *
 * ✗ THE PREVIOUS WRITE-UP WAS WRONG ON A FACT and it is corrected here: it claimed this
 * "matches size and structure EXACTLY" while also claiming mwcc adds +4B -- both cannot
 * be true. Measured: the old source compiles to 120, the ROM is 116. Never trust a size
 * claim in a note; re-run verify_idx.
 *
 * WHAT IT DOES (settled): if bit 0 of the hw60 lo byte is set, publish the pending slot
 * (owner+0x1c9 -> owner+0x1c7), then hand the node's anchor point -- copied from
 * node_ref[1] with y raised by 0x900 -- to ov107_020c5c54, and advance with no callback.
 *
 * THE DIFF, and it is entirely in the 3-word copy:
 *      ROM:   ldr r2,[r0,#4] ; ldm r2,{r2,r3,ip} ; add r3,r3,#0x900
 *             str r2,[sp] ; str r3,[sp,#4] ; str ip,[sp,#8]          (5 after the ldr)
 *      mine:  ldm+stm (the struct copy), then ldr [sp,#4] ; add ; str [sp,#4]  (6)
 * The ROM groups all three LOADS into one ldm, bumps y in-register, and stores the three
 * words individually -- it never emits an stm. Every source form I can write either
 * groups the loads AND the stores (struct copy -> ldm+stm, then a re-load to bump y), or
 * groups neither (field-wise -> three ldr/str pairs).
 *
 * PRE-PARK CHECKLIST -- all four run:
 *  1. --thumb: ARM is right; this is a 116 B ARM function.
 *  2. Arity: CHECKED CAREFULLY, and there is a trap here worth recording.
 *     - The real definition `void func_ov107_020c5c54(char *node)` (a matched file in
 *       ov107) shows ONE parameter -- but that proves nothing: an UNUSED trailing
 *       parameter is invisible in the callee's own code, so a callee body can never
 *       settle its own arity. Only callers can.
 *     - Matched callers elsewhere pass TWO (`func_ov107_020c5c54(*(int *)child, &buf)`),
 *       and the ROM sets r0/r1 here. Two is right.
 *     - ⚠ `grep` also turns up `extern void func_ov107_020c5c54(void *r0, int r1, int r2,
 *       int r3)` -- FOUR args. That comes from the asm_stubs of THIS family
 *       (ov294/295/296), i.e. an auto-generated declaration on an ASM blob. It is not
 *       evidence, exactly as asm_stubs are excluded from every other census.
 *  3. No constant is in the wrong register.
 *  4. Diff read back: one instruction, all of it in the copy.
 *
 * RULED OUT (10 spellings; the number is the size each produced, ROM = 116):
 *   struct copy then `stk.y += 0x900`                                  120  <- closest
 *   three scalars loaded, then stored with the bump at store time      120
 *   the modified field loaded FIRST, then the other two                120
 *   the original's a/b/c scalars (what the old note describes)         120
 *   field-wise through a struct pointer (`stk.x = p->x; ...`)          124
 *   field-wise through an int pointer (`stk[0] = p[0]; ...`)           124
 *   all three in ONE declaration statement                             124
 *   struct temp `t = *p`, then field-wise out                          136
 *   const struct temp, then field-wise out                             136
 *   struct temp, bump t.y, then `stk = t`                              132
 *
 * NEXT STEP: the lever is whatever makes mwcc group the three LOADS without also
 * grouping the three stores. Nothing in the ten forms above separates those two
 * decisions -- they are made together by the same peephole. An idea not yet tried:
 * something that makes the three destination slots non-adjacent to the optimiser (e.g.
 * the outgoing block declared as three separate locals that happen to be laid out
 * consecutively) so the stores cannot merge while the loads still can.
 */
extern void func_ov107_020c5c54(int node, void *blk);
extern int func_0203c634(void *obj, int slot, int arg);

struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
struct v3 { int x, y, z; };

void func_ov294_020d1f94(void *param_1) {
    int *node_ref = *(int **)((char *)param_1 + 4);
    int node = *node_ref;

    if (((struct hw60 *)(node + 0x60))->lo & 1) {
        struct v3 stk;
        *(signed char *)(node + 0x1c7) = *(signed char *)(node + 0x1c9);
        stk = *(struct v3 *)node_ref[1];
        stk.y += 0x900;
        func_ov107_020c5c54(*node_ref, &stk);
        func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), 0);
    }
}
