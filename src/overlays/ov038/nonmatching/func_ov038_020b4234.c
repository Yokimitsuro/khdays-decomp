/*
 * func_ov038_020b4234 -- UNFINISHED. 192/192 bytes, 48/48 instructions.
 * x4 family (ov057_020b6a34 / ov077_020b9114 / ov094_020bb7d4) -> worth 4.
 * ONE callee-saved register apart.
 *
 * WHAT IT DOES: set the emitter's mode word from the requested mode (0->1, 1->3, 2->2,
 * 3->3; anything else leaves it alone), then for each of the 5 slots: if the slot still
 * holds a handle, release it (02014dc4) and clear it; then rebind the slot to the current
 * source (0202accc, with the mode as a short) and reset it (01fff774). Note the release is
 * conditional but the rebind is NOT -- the `beq` skips only the release+clear, not the two
 * calls. param_1 is unused.
 *
 * The case order came straight from tools/switchorder.py and is the natural 0,1,2,3 here,
 * so the whole layout including the jump table was right on the first compile.
 *
 * THE DIFF: `self` lands in r7 where the ROM puts it in r6. Five values compete for the
 * five callee-saved registers -- self, the loop counter, the short mode, and TWO separate
 * zeros (both live across a call, which is why they are callee-saved at all):
 *      ROM:   self=r6  i=r5  m=r8  zero=r4  zero=r7
 *      mine:  self=r7  ...
 * Everything else -- opcodes, operands, the table, the loop, all three calls -- matches.
 *
 * PRE-PARK CHECKLIST -- all four run:
 *  1. --thumb: ARM gives the exact 192/192.
 *  2. Arity: 02014dc4 1 · 0202accc 4 · 01fff774 3, all matching the ROM's register setup.
 *  3. No constant is in the wrong register: both zeros are present and both callee-saved,
 *     exactly as in the ROM.
 *  4. Diff read back: 48 vs 48, one register.
 *
 * RULED OUT (4 spellings):
 *   `short m; int i;` instead of `int i; short m;`   -> same diff at 0x5
 *   `int m` instead of `short m`                     -> 200 B: the short cast is LOAD-BEARING
 *   `m = (short)mode` computed BEFORE the switch     -> diff moves to 0x4 (worse); the ROM
 *                                                       emits the cast after the switch
 *   `self` taken through a local instead of directly -> same diff at 0x5
 *
 * NEXT STEP: the callee-saved-permutation class. The one thing NOT tried: giving the two
 * zeros explicit names. They are compiler temps here, and they are the only values whose
 * count and ordering I have not been able to influence from the source -- which is exactly
 * what decides who gets r6.
 */
extern void func_02014dc4(void *p);
extern void func_0202accc(void *p, unsigned short i, int a, short m);
extern void func_01fff774(void *p, unsigned short i, int z);

void func_ov038_020b4234(int p0, int *self, int mode) {
    int i;
    short m;

    switch (mode) {
    case 0: self[0] = 1; break;
    case 1: self[0] = 3; break;
    case 2: self[0] = 2; break;
    case 3: self[0] = 3; break;
    }
    m = (short)mode;
    for (i = 0; i < 5; i++) {
        if (self[i + 4] != 0) {
            func_02014dc4((char *)self + 0x24);
            self[i + 4] = 0;
        }
        func_0202accc((char *)self + 4, (unsigned short)i, self[0x43], m);
        func_01fff774((char *)self + 4, (unsigned short)i, 0);
    }
}
