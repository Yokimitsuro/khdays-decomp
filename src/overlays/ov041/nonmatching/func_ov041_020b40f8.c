/*
 * func_ov041_020b40f8 -- UNFINISHED. 304 vs 300: ONE instruction. x4 family -> worth 4.
 *
 * WHAT IT DOES: drive the emitter's 5-state machine. First, unless it is already idle (0)
 * or stopping (4), and the owner is neither busy (ov022_02095524) nor in mode 0x30, force
 * it to state 4 and retune. Then: 0 idle; 1 -> retune with 0, advance to 2 and fall into
 * the shared tail; 2 -> straight to the tail; 3 -> just poll; 4 -> poll and go idle when it
 * reports done. The tail polls (0202a818) and, once it reports done, retunes with 1 and
 * advances to 3.
 *
 * ★ THE FINDING, and it is the whole gap: the ROM puts a one-instruction case body INSIDE
 * the jump table slot. `case 0: return;` and `default: return;` are each a bare
 * `pop {r4,r5,r6,pc}` sitting where a branch would go -- two slots, two instructions, no
 * branch and no shared epilogue block. mwcc from clean C merges the two identical bodies
 * and branches to one shared `pop`: 2 branches + 1 pop = 3 instructions.
 *      ROM:   pop {r4,r5,r6,pc} ; pop {r4,r5,r6,pc} ; b +0x90 ; b +0xbc ; b +0x100 ; b +0x110
 *      mine:  b +0xe8 ; b +0xe8 ; b +0x90 ; b +0xec ; b +0xc0 ; b +0xd0   (+ the shared pop)
 * Measured: merging `case 0:` with `default:` is 304 (1 over); writing them as two separate
 * `return;` statements -- in either order -- is 308 (2 over, since mwcc then emits two
 * branches AND two pops). So merging is strictly better and is kept below, but neither
 * reaches the ROM's slot-inlined form.
 *
 * ⚠ tools/switchorder.py was FIXED because of this function: it assumed every table slot is
 * a `b`, and choked on the inline `pop`. It now reports "INLINE IN THE TABLE SLOT" instead,
 * which is information Ghidra does not give you at all. Expect more of these across the
 * ~570-function dense-dispatcher vein.
 *
 * PRE-PARK CHECKLIST:
 *  1. --thumb: ARM is right (the size is exact-ish at 304 vs 300; THUMB is nonsense here).
 *  2. Arity: ov022_02095524(p) 1 · 0202accc(p, 2, q, k) 4 · 01fff774(p, 2, k) 3 ·
 *     0202a818(p, p3) 2. All match the ROM's register setup.
 *  3. No constant is in the wrong register -- the whole prologue, including the shared
 *     `mov r1,#2 ; mov r3,r1` pair, is byte-identical.
 *  4. Diff read back: everything up to the table matches exactly; only the table slots and
 *     the epilogue duplication differ.
 *
 * NEXT STEP: find what makes mwcc duplicate a one-instruction epilogue into the table slot
 * rather than share it. The ROM duplicates `pop` freely here (six of them in 300 bytes), so
 * this is not a size/speed tradeoff it is unaware of -- something about how the returns are
 * written is telling it they are distinct.
 */
extern int func_ov022_02095524(void *p);
extern void func_0202accc(void *p, int a, void *b, int c);
extern void func_01fff774(void *p, int a, int b);
extern unsigned int func_0202a818(void *p, int a);

void func_ov041_020b40f8(int self, int *p, int p3) {
    if (*p != 0 && *p != 4 && func_ov022_02095524((void *)(self + 0x22f8)) == 0 &&
        *(int *)(self + 0x6bc) != 0x30) {
        *p = 4;
        func_0202accc((char *)p + 4, 2, (char *)p + 0xe4, 2);
        func_01fff774((char *)p + 4, 2, 2);
    }
    switch (*p) {
    case 1:
        func_0202accc((char *)p + 4, 2, (char *)p + 0xe4, 0);
        func_01fff774((char *)p + 4, 2, 0);
        *p = 2;
        break;
    case 2:
        break;
    case 3:
        func_0202a818((char *)p + 4, p3);
        return;
    case 4:
        if (func_0202a818((char *)p + 4, p3) != 0) {
            *p = 0;
        }
        return;
    case 0:
    default:
        return;
    }
    if (func_0202a818((char *)p + 4, p3) == 0) {
        return;
    }
    func_0202accc((char *)p + 4, 2, (char *)p + 0xe4, 1);
    func_01fff774((char *)p + 4, 2, 1);
    *p = 3;
}
