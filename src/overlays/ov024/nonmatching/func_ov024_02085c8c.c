/* func_ov024_02085c8c -- MobiClip: decode one audio entry for the current channel.
 *
 * Does nothing once the consumed count (+0xcc) has caught up with the available count (+0xc8).
 * The coding is a u16 at +0x1c and picks the decoder; each one leaves the bitstream cursor
 * (*(int **)(ctx + 0x34)) advanced past exactly what it read:
 *   0  nothing to do
 *   1  FastAudio transform (func_ov024_02086958) -- it reports how many bytes it consumed
 *   2  the 0x28-byte coding (func_ov024_02087318_unk)
 *   3  IMA ADPCM: a 4-byte state header, but only on the first entry of a frame (+0xa4 == 1),
 *      then 0x80 bytes of nibbles
 *   else raw PCM: 0x200 bytes copied straight to the destination
 *
 * Per-channel state is an array at +0x58 with a stride of 0x14f8 -- that is a POOL LITERAL, not a
 * data symbol (this function's only relocs are its five calls), and it matches the stride field
 * the transform reads from its own block at +0x14f4. The channel index is +0xd0 and wraps at the
 * channel count (+0x1e), which also clears the ADPCM first-entry flag.
 *
 * Ov024_Chan is a static inline on purpose: the ROM re-derives the channel pointer at every use
 * (fresh ldr +0x58 / ldr +0xd0 / mla each time) rather than keeping it in a register.
 *
 * NONMATCHING: 432/432 bytes, byte-exact through 0x54. The only difference is an r1/r2 swap in
 * the SECOND channel derivation (the `chan[1] = dst` store): the ROM loads +0x58 into r1 and
 * +0xd0 into r2 there, mwcc mirrors the pair. Its first derivation (mul + register-offset store,
 * which is the tricky one) and its third both match exactly -- the ROM itself uses the opposite
 * pair in the second and third, so this is the allocator picking freely, not a pattern to model.
 * Tried and rejected: swapping the helper's addition order to channel*stride + base -- no change.
 * Regalloc-permutation class, see deferred-ties.md.
 */
extern int func_ov024_02086958(char *chan);
extern int func_ov024_02087318_unk(char *chan);
extern void func_ov024_020867ec(char *chan, int src);
extern void func_ov024_02086800(char *chan, int src, int n, void *dst);
extern void MIi_CpuCopy16(const void *src, void *dest, unsigned int size);

static inline char *Ov024_Chan(int ctx) {
    return (char *)(*(int *)(ctx + 0x58) + *(int *)(ctx + 0xd0) * 0x14f8);
}

int func_ov024_02085c8c(int ctx, void *dst) {
    unsigned int coding;

    if (*(int *)(ctx + 0xcc) == *(int *)(ctx + 0xc8)) {
        return 0;
    }
    coding = *(unsigned short *)(ctx + 0x1c);
    if (coding == 0) {
        return 0;
    }

    if (coding == 1) {
        *(int *)Ov024_Chan(ctx) = **(int **)(ctx + 0x34);
        *(void **)(Ov024_Chan(ctx) + 4) = dst;
        **(int **)(ctx + 0x34) += func_ov024_02086958(Ov024_Chan(ctx));
    } else if (coding == 2) {
        *(int *)Ov024_Chan(ctx) = **(int **)(ctx + 0x34);
        *(void **)(Ov024_Chan(ctx) + 4) = dst;
        func_ov024_02087318_unk(Ov024_Chan(ctx));
        **(int **)(ctx + 0x34) += 0x28;
    } else if (coding == 3) {
        if (*(int *)(ctx + 0xa4) == 1) {
            func_ov024_020867ec(Ov024_Chan(ctx), **(int **)(ctx + 0x34));
            **(int **)(ctx + 0x34) += 4;
        }
        func_ov024_02086800(Ov024_Chan(ctx), **(int **)(ctx + 0x34), 0x80, dst);
        **(int **)(ctx + 0x34) += 0x80;
    } else {
        MIi_CpuCopy16((void *)**(int **)(ctx + 0x34), dst, 0x200);
        **(int **)(ctx + 0x34) += 0x200;
    }

    *(int *)(ctx + 0xd0) += 1;
    if (*(int *)(ctx + 0xd0) == *(unsigned short *)(ctx + 0x1e)) {
        *(int *)(ctx + 0xd0) = 0;
        *(int *)(ctx + 0xa4) = 0;
    }
    *(int *)(ctx + 0xcc) += 1;
    return 1;
}
