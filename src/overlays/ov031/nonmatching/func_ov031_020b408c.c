/*
 * func_ov031_020b408c  (x4 family: ov031/ov050/ov070/ov088)  148 bytes
 *
 * Two structurally-identical 3-iteration loops that publish sub-object slot
 * pointers into a doubly-indexed table.  Semantically equivalent, byte-exact
 * EXCEPT a 1-instruction rematerialization tie:
 *   - orig keeps `this` live (fp) and RECOMPUTES `blk = this + 0x2000` at the
 *     top of the 2nd loop (`add r7,fp,#0x2000`), holding base(this+0x2c2c) in r6.
 *   - mwcc from any equivalent C instead HOLDS `blk` across both loops (r6) and
 *     drops `this`, so the 2nd recompute is elided => 144 bytes (1 instr short).
 * Tried: blk as held local (144, short), blk reassigned per loop (still CSE'd to
 * 144), inline sl-start from `this` with no base local (152, long). This is the
 * held-value-vs-rematerialize class under equal 10-register pressure; unsteerable
 * by source form. asm stub stays byte-exact; this file is the PC-port reference.
 */
extern void func_ov022_020b15a4(int a, int b);

void func_ov031_020b408c(int this) {
    int blk = this + 0x2000;
    int base = this + 0x2c2c;
    int entry, sl, off, i;

    entry = *(int *)(blk + 0x644);
    off = 0;
    sl = base + 0x2a8;
    for (i = 0; i < 3; i++) {
        int p = *(int *)(entry + 0x6c);
        func_ov022_020b15a4(*(int *)(blk + 0x63c), sl);
        *(int *)(p + off + 0x130) = sl;
        off += 0x1c8;
        sl += 0x24;
    }

    entry = *(int *)(blk + 0x644);
    off = 0;
    sl = base + 0x23c;
    for (i = 0; i < 3; i++) {
        int p = *(int *)(entry + 0xc);
        func_ov022_020b15a4(*(int *)(blk + 0x640), sl);
        *(int *)(p + off + 0x130) = sl;
        off += 0x1c8;
        sl += 0x24;
    }
}
