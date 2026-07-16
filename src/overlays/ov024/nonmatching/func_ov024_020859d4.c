/* func_ov024_020859d4 -- MobiClip: decode one video frame by entering the ITCM blob.
 *
 * This is the call site for the position-independent decoder: ctx+0x38 holds the blob pointer
 * (put there by MobiClip_InitDecoder) and it is entered with the decoder state block, returning
 * the number of bytes it consumed, which the bitstream cursor then advances by.
 *
 * The top bit of the frame's first u16 says whether an audio entry rides along: it sets the
 * first-entry flag at +0xa4 that MobiClip_DecodeAudioEntry reads, and in an N3 container it also
 * costs a further 4 bytes of header -- that is the byte-wise 'N','3' check plus the +4 advance.
 * An N2 container skips the +4 even when the bit is set.
 *
 * Afterwards the decoded plane (block +0x3b4) is published into the ring at +0x64[+0xac], the
 * audio consumed/channel counters are reset, all six ring cursors step and wrap at the ring size
 * (+0xa8), and the frame count (+0xa0) advances.
 *
 * NONMATCHING: 228/228 bytes, byte-exact through 0xa4. Everything -- the guard, the 0x8000 test,
 * the blob call, the N3 check, the publish and the frame bump -- matches. Only the ring loop's
 * ADDRESSING MODE differs: the ROM computes `add r3,r5,r4,lsl#2` inside the loop and reaches the
 * cursor as `[r3,#0xac]`, while mwcc hoists `add r3,r5,#0xac` out and uses `[r3,r4,lsl#2]`. Same
 * instruction count, same size -- it just picks the other half of the addressing mode.
 *
 * Tried, all three forms:
 *   ((int *)(ctx + 0xac))[i]           -> hoisted base + register offset (this one; right SIZE)
 *   *(int *)(ctx + 0xac + i * 4)       -> induction pointer, +4 B
 *   *(int *)(Slot(ctx, i) + 0xac)      -> induction pointer, +4 B
 * ⚠ Note the subscript form did NOT behave as codegen-cracks.md predicts here -- the catalog says
 * `((int*)(base+K))[i]` yields the ROM's `add rN,base,i,lsl#2 ; ldr [rN,#K]`, and it does in
 * func_ov024_0208589c's loop, but in this (simpler) loop body it yields the hoisted base instead.
 * The crack is real but context-dependent; measure, don't assume.
 *
 * The `!= 0` sense of the 0x8000 test IS load-bearing and must stay: written as `== 0` first,
 * mwcc predicates BOTH arms and drops the ROM's `beq` (-4 B). Inverting it makes mwcc predicate
 * the zero arm and branch over the other, which is what the ROM does.
 */

int func_ov024_020859d4(int ctx) {
    int extra;
    int i;

    if ((unsigned int)*(int *)(ctx + 0x9c) > (unsigned int)*(int *)(ctx + 0xa0)) {
        return 0;
    }

    if ((*(unsigned short *)**(int **)(ctx + 0x34) & 0x8000) != 0) {
        *(int *)(ctx + 0xa4) = 1;
        extra = 4;
    } else {
        extra = 0;
        *(int *)(ctx + 0xa4) = 0;
    }

    **(int **)(ctx + 0x34) += (*(int (**)(int))(ctx + 0x38))(*(int *)(ctx + 0x34));

    if (*(signed char *)(ctx + 8) == 0x4e && *(signed char *)(ctx + 9) == 0x33) {
        **(int **)(ctx + 0x34) += extra;
    }

    *(int *)(*(int *)(ctx + 0x64) + *(int *)(ctx + 0xac) * 4) =
        *(int *)(*(int *)(ctx + 0x34) + 0x3b4);
    *(int *)(ctx + 0xcc) = 0;
    *(int *)(ctx + 0xd0) = 0;

    for (i = 0; i < 6; i++) {
        ((int *)(ctx + 0xac))[i] = ((int *)(ctx + 0xac))[i] + 1;
        if (*(int *)(ctx + 0xa8) == ((int *)(ctx + 0xac))[i]) {
            ((int *)(ctx + 0xac))[i] = 0;
        }
    }

    *(int *)(ctx + 0xa0) = *(int *)(ctx + 0xa0) + 1;
    return 1;
}
