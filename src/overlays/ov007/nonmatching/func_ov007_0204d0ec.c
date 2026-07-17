/* UNFINISHED. 132/132 bytes, 33/33 instructions -- ov007 is 12/14 and this is one of
 * the two functions standing between it and 100%.
 *
 * The whole diff is TWO predicated instructions swapped in the empty-line branch:
 *      ROM:   streq r0,[r4,#0x20]  ;  ldreq r2,[pc,#0x34]      (store, then load)
 *      mine:  ldreq r2,[pc,#0x38]  ;  streq r0,[r4,#0x20]
 * Everything else -- both arms, the B-button block, the 0 hoisted into r0 and reused by
 * all three stores, `ret` living in r2 -- is identical.
 *
 * RULED OUT (2026-07-17, and the last two are worth NOT repeating because they prove the
 * structure below is right):
 *   the else branch's two statements written in the other order   -> same diff at 0x34
 *   the shared `*(root+0x20) = 0` hoisted out of both arms        -> 128 B, 4 SHORT
 *   the test negated so the empty-line case is the `if`           -> 140 B, 8 OVER
 * So the arm shapes and the duplicated store are both load-bearing; only the order inside
 * the predicated block is left, and the source cannot express it (mwcc schedules the pool
 * load ahead of the store either way).
 *
 * An earlier note here claimed "no mwcc generation matches (verify_sweep)". Treat that as
 * a prior, not a verdict: 12,191 functions match byte-exactly with this exact compiler, so
 * a build difference is the least likely explanation, not the first. */
extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov007_0204ce94(void *p);
extern int func_ov007_0204d170(void);
extern int func_ov007_0204cf7c(void);
extern unsigned short data_0204c190;
extern int func_ov007_0204d2d0(void);

/* After a 0xf-frame delay, pull the next text line (Ov007_CopyLine): if non-empty
 * bump the line counter and loop to cf7c, else advance to the next screen (d170).
 * The B-button (input bit 8) skips straight to the fade-out (d2d0). */
int func_ov007_0204d0ec(void) {
    int root = NNSi_FndGetCurrentRootHeap();
    int ret = 0;
    int frame = *(int *)(root + 0x20) + 1;

    *(int *)(root + 0x20) = frame;
    if (frame >= 0xf) {
        func_ov007_0204ce94((void *)root);
        if (*(unsigned short *)(root + 0x7c) != 0) {
            *(int *)(root + 0x70) = *(int *)(root + 0x70) + 1;
            ret = (int)func_ov007_0204cf7c;
            *(int *)(root + 0x20) = 0;
        } else {
            *(int *)(root + 0x20) = 0;
            ret = (int)func_ov007_0204d170;
        }
    }
    if ((data_0204c190 & 8) != 0) {
        *(int *)(root + 0x20) = 0;
        ret = (int)func_ov007_0204d2d0;
    }
    return ret;
}
