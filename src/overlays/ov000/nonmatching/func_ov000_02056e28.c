/* func_ov000_02056e28 -- apply one command record to the accumulator, by command id (+4).
 *   1: for each of the four slots that has a payload (+0x1c), submit it through
 *      func_ov000_02056bac at (slot's +0x20 offset) + the record's base (+0xc) - 1.
 *   3: same four slots, but submitted through func_ov000_02056b18 with the slot's +0x22 --
 *      and then FALLS THROUGH into case 6. That is deliberate: a type-3 record both submits
 *      its slots and applies its deltas.
 *   6: add the seven deltas at +0x88.. onto +0x78.., then the fourteen counters at +0xa4..
 *      onto +0x94.., each saturating at 0x64000.
 * Any other id does nothing.
 *
 * ⚠ NONMATCHING — and NOT a proven tie. 348/360, twelve bytes SHORT. This is unfinished work,
 * parked here rather than deleted because the semantics above are read off the disassembly and
 * are worth keeping. It blocks a 6-member family (ov000/004/005/008/009/025), so it is worth
 * finishing.
 *
 * What is already right: the switch (including the deliberate case 3 -> case 6 fallthrough), both
 * slot loops, and all seven scalar deltas.
 * What is wrong: only the final 14-counter loop's addressing. The ROM derives two bases per
 * iteration and uses immediate offsets (`add r4,r6,r0,lsl #2 ; ldr r3,[r4,#0x94]`); mwcc hoists
 * `dst+0x94` and `src+0xa4` out and uses register offsets (`ldr r4,[r5,r0,lsl #2]`) -- fewer
 * instructions, which is why we come out short, not long.
 * Tried: array-subscript form, and a static-inline slot helper returning `base + i*4` (the shape
 * that worked for func_ov000_0208589c). mwcc CSEs the helper away here. The index-vs-induction
 * crack in codegen-cracks.md is explicitly context-dependent; this is another context where the
 * usual two forms are not enough. A third form is needed -- do not just re-try those two. */
extern void func_ov000_02056bac(int dst, int payload, int pos, int a, int b);
extern void func_ov000_02056b18(int dst, int payload, int pos, int a);

/* The counter loop must derive `base + i*4` and reach the field with an immediate offset, which
 * is what an inlined helper gives. Array-subscript form hoists the bases and uses register
 * offsets instead (`ldr r4,[r5,r0,lsl #2]`) -- same count, wrong shape. */
static inline char *Ov000_Slot(int base, int i) {
    return (char *)(base + i * 4);
}

void func_ov000_02056e28(int dst, int src) {
    int i;

    switch (*(int *)(src + 4)) {
    case 1:
        for (i = 0; i < 4; i++) {
            if (*(int *)(src + i * 8 + 0x1c) != 0) {
                func_ov000_02056bac(dst, *(int *)(src + i * 8 + 0x1c),
                                    *(unsigned short *)(src + i * 8 + 0x20)
                                        + (*(int *)(src + 0xc) - 1),
                                    0, 1);
            }
        }
        break;

    case 3:
        for (i = 0; i < 4; i++) {
            if (*(int *)(src + i * 8 + 0x1c) != 0) {
                func_ov000_02056b18(dst, *(int *)(src + i * 8 + 0x1c),
                                    *(unsigned short *)(src + i * 8 + 0x22), 1);
            }
        }
        /* falls through */
    case 6:
        *(int *)(dst + 0x78) = *(int *)(dst + 0x78) + *(int *)(src + 0x88);
        *(int *)(dst + 0x7c) = *(int *)(dst + 0x7c) + *(int *)(src + 0x8c);
        *(int *)(dst + 0x80) = *(int *)(dst + 0x80) + *(int *)(src + 0x90);
        *(int *)(dst + 0x84) = *(int *)(dst + 0x84) + *(int *)(src + 0x94);
        *(int *)(dst + 0x88) = *(int *)(dst + 0x88) + *(int *)(src + 0x98);
        *(int *)(dst + 0x8c) = *(int *)(dst + 0x8c) + *(int *)(src + 0x9c);
        *(int *)(dst + 0x90) = *(int *)(dst + 0x90) + *(int *)(src + 0xa0);
        for (i = 0; i < 0xe; i++) {
            *(int *)(Ov000_Slot(dst, i) + 0x94) =
                *(int *)(Ov000_Slot(dst, i) + 0x94) + *(int *)(Ov000_Slot(src, i) + 0xa4);
            if (*(int *)(Ov000_Slot(dst, i) + 0x94) > 0x64000) {
                *(int *)(Ov000_Slot(dst, i) + 0x94) = 0x64000;
            }
        }
        break;
    }
}
