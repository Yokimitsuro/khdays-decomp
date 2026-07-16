/* func_ov231_020ccc48 -- probe a direction: gather the candidates, skip the ones already handled,
 * and report the first that answers. Returns 1 on a hit, 0 if nothing answered.
 *
 * `kind` picks the gather: non-zero goes through func_ov107_020c8eb8 with it, zero uses
 * func_ov107_020c8f44 with the query block instead. Either fills a 4-entry list on the stack and
 * returns how many are in it.
 *
 * Each candidate carries a small id at +2; `1 << id` (kept to a byte) is its bit in the mask at
 * ctx+0x4d, so a candidate already marked there is skipped. A candidate that passes
 * func_ov107_020ca918 gets marked, and effect 0 fires at its position raised by 0x2000 -- then
 * the probe stops and reports the hit.
 *
 * The position vector is passed BY VALUE to func_ov107_020c0b90, which is what the `sub r3,sp,#8`
 * is: mwcc straddles the struct across sp so two words load into r2/r3 and the third is already
 * in the outgoing stack slot.
 *
 * ------------------------------------------------------------------------------------------
 * NONMATCHING: 272/272 bytes. Every instruction matches one-for-one -- same opcodes, same order,
 * same stack layout (pos@sp+8, list@sp+0x14). It is a pure REGISTER PERMUTATION, and all of it
 * cascades from ONE thing: where the 5th (stack) parameter gets loaded.
 *
 *   ROM:  ldr r4,[sp,#0x48]  at 0x10 (before ctx), then `and r4,r4,#0xff` at 0x4c
 *   mine: ldr r0,[sp,#0x48]  at 0x48 (after the gather call), mask right after
 *
 * The ROM homes the parameter at entry and keeps it live across the gather call; mwcc sinks the
 * load to its use instead. Resulting map:
 *   ROM   r4=flags r6=ctx r7=i  r5=listbase r8=bit
 *   mine  r8=flags r5=ctx r6=i  r4=listbase r7=bit
 *
 * Tried and rejected (do not repeat):
 *   - `unsigned char flags` parameter -> drops the `and` entirely, 268/272;
 *   - `int f = flags;` as the FIRST declaration-initialiser, ahead of ctx's -- that lever works
 *     for emission order elsewhere (see func_ov231_020cd920) but mwcc sinks a parameter load
 *     regardless, so it does not move;
 *   - `f & 0xff` at the use vs at the declaration: no effect on the load position.
 *
 * This is the known regalloc/frame-arg-home tie class. Retry only under a different mwcc build;
 * the semantics above are settled and should be reused, not re-derived. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern int func_ov107_020c8eb8(int owner, int kind, void **list);
extern int func_ov107_020c8f44(int owner, void *query, void **list);
extern int func_ov107_020ca918(void *cand, int owner, int owner2, int flags, void *pt, int a);
extern void func_ov107_020c0b90(int owner, int effect, VecFx32 v, int a);

int func_ov231_020ccc48(int self, int kind, void *query, void *pt, int flags) {
    /* `f` is read before ctx because the ROM loads the stack parameter first (`ldr r4,[sp,#0x48]`
     * ahead of `ldr r6,[r0,#4]`) and keeps it in a callee-saved register across the gather call;
     * reading flags only at its use makes mwcc re-load it after the call instead, which cascades
     * into a different allocation for every register in the function. Declaration-initialisers
     * run in declaration order, so this is the lever. */
    int f = flags;
    int *ctx = *(int **)(self + 4);
    /* Reverse of their stack order: pos at sp+8, list at sp+0x14 (sp+0/+4 are outgoing args). */
    void *list[4];
    VecFx32 pos;
    int n;
    int i;
    int bit;

    if (kind != 0) {
        n = func_ov107_020c8eb8(ctx[0], kind, list);
    } else {
        n = func_ov107_020c8f44(ctx[0], query, list);
    }

    for (i = 0; i < n; i++) {
        bit = (1 << *(unsigned short *)((char *)list[i] + 2)) & 0xff;
        if (*(unsigned char *)((char *)ctx + 0x4d) & bit) {
            continue;
        }
        if (func_ov107_020ca918(list[i], ctx[0], ctx[0], f & 0xff, pt, 0) == 0) {
            continue;
        }

        pos = *(VecFx32 *)((char *)list[i] + 0x190);
        pos.y += 0x2000;
        *(unsigned char *)((char *)ctx + 0x4d) |= bit;
        func_ov107_020c0b90(ctx[0], 0, pos, 0);
        return 1;
    }

    return 0;
}
