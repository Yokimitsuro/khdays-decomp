/* Tear the ov002 context down for good: run the field teardown, free the eight
 * owned buffers at +0x34 (stride 4) and clear each slot, then free the context
 * itself and drop the global.
 *
 * The slot pointer walks by 4 while the field offset stays 0x34, so the array is
 * ctx[8] of pointers based at +0x34 -- the ROM advances the base rather than
 * indexing, and caching the base defeats it. */
extern void func_ov002_02071ae0(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

extern int data_ov002_0207fa10;

void func_ov002_02071958(void) {
    int i;
    char *slot = (char *)data_ov002_0207fa10;

    func_ov002_02071ae0();

    i = 0;
    do {
        if (*(void **)(slot + 0x34) != 0) {
            NNSi_FndFreeFromDefaultHeap(*(void **)(slot + 0x34));
        }
        *(void **)(slot + 0x34) = 0;
        i++;
        slot += 4;
    } while (i < 8);

    NNSi_FndFreeFromDefaultHeap((void *)data_ov002_0207fa10);
    data_ov002_0207fa10 = 0;
}

/* NOT MATCHING -- 2 instructions, size exact (56/56), all 6 relocs exact.
 *
 * Residue: the ROM stores the cleared slot BEFORE bumping the counter; mwcc bumps first.
 *     ROM   ... bl free ; str r6,[r5,#0x34] ; adds r4,r4,#1 ; adds r5,r5,#4 ; cmp r4,#8
 *     mwcc  ... bl free ; adds r4,r4,#1 ; str r6,[r5,#0x34] ; adds r5,r5,#4 ; cmp r4,#8
 * mwcc schedules the increment onto the `beq` target so it lands on the common path.
 *
 * Two things WERE solved and are kept here, so do not undo them:
 *   * `int i;` assigned AFTER func_ov002_02071ae0() rather than initialised at declaration.
 *     Initialising it in the declaration hoists `movs r4,#0` above the context load and
 *     costs the whole prologue (that was the original 0x4 residue).
 *   * declaration order `i` then `slot` -- it is what colours slot=r5 and i=r4. Reversed,
 *     the pair swaps.
 *
 * Ruled out for the remaining pair, all failing identically at 0x12: a `for` loop instead of
 * do/while; `while (++i < 8)` with the increment in the condition; `slot += 4;` written
 * before `i++`; and hoisting `(void **)(slot + 0x34)` into a local `p` (that one is worse --
 * 60 bytes, it stops mwcc CSE-ing the zero into r6). Duplicating the clear into both arms of
 * the if is also 60 bytes.
 *
 * The zero being stored comes from r6, which mwcc seeds from the counter's initial 0
 * (`adds r6,r4,#0`) -- the ROM does the same, so that part is right and is worth preserving
 * in any further attempt.
 */
