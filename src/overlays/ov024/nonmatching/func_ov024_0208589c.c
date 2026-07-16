/* func_ov024_0208589c -- MobiClip: step the container to the next frame index entry.
 *
 * Stops once the current frame (+0x98) reaches the frame count (+0xc). Otherwise it advances the
 * frame counter and flips the double-buffer slot (+0x90) between 0 and 1, then asks the source
 * object (ctx[0]) to advance through its vtable (+0x14).
 *
 * The index entry is one u32 read from the INCOMING slot's arrays, split as the container's
 * header describes:
 *   entry >> 14      18 bits -- the payload's byte size
 *   entry & 0x3fff   14 bits -- the sample/duration field
 * and stashed into the OUTGOING slot's arrays (+0x78 and +0x88). The four parallel arrays are
 * indexed by slot: +0x70 base, +0x78 size, +0x80 offset, +0x88 field.
 *
 * Unless this was the last entry, the payload itself is then read through the vtable's read
 * (+0x10) with size+4 -- the +4 skips the entry header -- and the result recorded at +0x80.
 * Finally the six per-plane pointers are refreshed from the tables at +0x5c/+0x60 (indexed
 * through +0xac) into the cursor struct at +0x34, and the available-sample count (+0xc8) is set
 * to the incoming slot's field times the channel count (u16 at +0x1e).
 *
 * The slot flip is a signed `% 2` -- that is what the lsr#31 / rsb lsl#31 / add ror#31 trio is.
 * 0x3fff is a pool literal, not a symbol: this function has zero relocs.
 *
 * Ov024_Slot must stay a static inline rather than a local: the ROM re-derives `ctx + slot*4`
 * once per STATEMENT (mwcc shares it across the loads within one statement, but not across
 * statements), which is exactly what an inlined helper reproduces.
 *
 * NONMATCHING: 308/312 -- FOUR bytes SHORT, one instruction. Structure, the slot addressing and
 * the loop all match. The gap: mwcc parks the outgoing slot pointer in the callee-saved r4
 * (`add r4,r5,r4,lsl#2`), which kills `old` but survives the vtable call, so it never needs to
 * re-derive afterwards. The ROM instead keeps `old` in r4 and re-derives into r1 after the call
 * (`add r1,r5,r4,lsl#2` at 0xc8) -- then reuses r4 as the loop counter. Registers are shifted by
 * one throughout as a knock-on.
 *
 * Three knobs got it from 324 to 308 and are all applied -- keep them if you retry:
 * 1. The slot flip is a signed `% 2`. Writing it as such reproduces the ROM's
 *    lsr#31 / rsb lsl#31 / add ror#31 trio exactly; nothing else does.
 * 2. Address the parallel arrays as `slot_base + 0x70/0x78/0x80`, NOT `ctx + 0x70 + slot*4`.
 *    The latter builds three separate bases and register-offset loads (+12 B); the former gives
 *    the ROM's one `add r3,r5,r1,lsl#2` plus three immediate-offset loads.
 * 3. The 6-iteration loop must use ARRAY SUBSCRIPT form -- `((int *)(base + K))[i]`. Written as
 *    `*(int *)(base + i*4 + K)` mwcc strength-reduces it to an induction pointer (`mov r4,r5`,
 *    `add ip,ip,#4`), where the ROM recomputes `add r3,r5,r4,lsl#2` every iteration. This is the
 *    documented index-vs-induction crack and it is worth 8 B here.
 */

static inline char *Ov024_Slot(int ctx, int slot) {
    return (char *)(ctx + slot * 4);
}

int func_ov024_0208589c(int ctx) {
    int old;
    int obj;
    unsigned int entry;
    int i;

    if (*(int *)(ctx + 0x98) == *(int *)(ctx + 0xc)) {
        return 0;
    }
    *(int *)(ctx + 0x98) = *(int *)(ctx + 0x98) + 1;
    old = *(int *)(ctx + 0x90);
    *(int *)(ctx + 0x90) = (old + 1) % 2;

    obj = *(int *)ctx;
    (*(void (**)(int))(*(int *)obj + 0x14))(obj);

    entry = *(unsigned int *)(*(int *)(Ov024_Slot(ctx, *(int *)(ctx + 0x90)) + 0x70)
                              + (*(int *)(Ov024_Slot(ctx, *(int *)(ctx + 0x90)) + 0x80)
                                 + *(int *)(Ov024_Slot(ctx, *(int *)(ctx + 0x90)) + 0x78)));
    *(unsigned int *)(Ov024_Slot(ctx, old) + 0x78) = entry >> 14;
    *(unsigned int *)(Ov024_Slot(ctx, old) + 0x88) = entry & 0x3fff;

    *(int *)*(int *)(ctx + 0x34) = *(int *)(Ov024_Slot(ctx, *(int *)(ctx + 0x90)) + 0x70)
                                   + *(int *)(Ov024_Slot(ctx, *(int *)(ctx + 0x90)) + 0x80);

    if (*(unsigned int *)(ctx + 0x98) < *(unsigned int *)(ctx + 0xc)) {
        obj = *(int *)ctx;
        *(int *)(Ov024_Slot(ctx, old) + 0x80) =
            (*(int (**)(int, int, int))(*(int *)obj + 0x10))(
                obj, *(int *)(Ov024_Slot(ctx, old) + 0x70),
                *(int *)(Ov024_Slot(ctx, old) + 0x78) + 4);
    }

    for (i = 0; i < 6; i++) {
        ((int *)(*(int *)(ctx + 0x34) + 0xc))[i] =
            ((int *)*(int *)(ctx + 0x5c))[((int *)(ctx + 0xac))[i]];
        ((int *)(*(int *)(ctx + 0x34) + 0x24))[i] =
            ((int *)*(int *)(ctx + 0x60))[((int *)(ctx + 0xac))[i]];
    }

    *(int *)(ctx + 0xc8) =
        *(unsigned short *)(ctx + 0x1e)
        * *(int *)(Ov024_Slot(ctx, *(int *)(ctx + 0x90)) + 0x88);
    return 1;
}
