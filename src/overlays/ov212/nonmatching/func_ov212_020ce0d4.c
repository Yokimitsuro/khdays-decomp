/* UNFINISHED -- 76/76 bytes, 19/19 instructions. Correct in every respect except a two-register
 * SCRATCH SWAP, which is the whole diff. Worth 3: ov266_020cfecc / ov267_020d1cec are byte-
 * identical twins waiting on dedupprop. (2026-07-17)
 *
 * THE ENTIRE DIFF:
 *     ROM:  mov r3, #0   ...  add ip, r0, #0x400  ...  stm ip, {...}  ...  mov r1, r3
 *     mine: mov ip, #0   ...  add r3, r0, #0x400  ...  stm r3, {...}  ...  mov r1, ip
 * Both the shared `0` and the +0x4e4 address must live in r3 or ip (the ldm clobbers r0-r2), so
 * there are exactly two registers for two values and mwcc picks the opposite assignment. Every
 * other instruction, offset and constant matches, including the 0x4e4 split (0xe4 + 0x400) and the
 * `lsl #0x10 ; asr #0x10` sign-extend of `id`.
 *
 * RULED OUT -- ten variants, and NONE of them moved the swap:
 *   statement order (6 permutations of the three zero-stores vs the vec copy):
 *     dc/e0/e1/cp, dc/e0/cp/e1, dc/cp/e0/e1, dc/e1/e0/cp, e0/e1/dc/cp  -> all identical (diff @0x9)
 *     cp/dc/e0/e1 -> 72 bytes (mwcc finds a shorter schedule; wrong)
 *   structural (4):
 *     a named `int zero = 0;` local            -> identical
 *     `unsigned char` instead of `signed char` -> identical
 *     a `VecFx32 *dst` local for the copy      -> identical
 *     `short id` param instead of `(short)id`  -> 72 bytes (wrong)
 * So this is neither statement-order nor type driven. It is a pure allocator coin-flip between the
 * only two scratch registers available at that point.
 *
 * NEXT IDEA (untried): find a form where the shared `0` and the copy destination do NOT compete --
 * e.g. something that makes the 0 die before the ldm, so only one value needs r3/ip. The `0` is
 * live across the copy purely because func_0203b9fc's 2nd argument reuses it (`mov r1, r3`); if the
 * ROM's source spelled that argument in a way that rematerialises it instead, the pressure changes.
 *
 * ---- what it does ----------------------------------------------------------------------------
 *
 * Reset the tracking block and re-point the emitter. Zeroes the counter at +0x5dc and the two flag
 * bytes at +0x5e0/+0x5e1, parks the vector at +0x4e4 back on the constant data_02041dc8, and pushes
 * the (16-bit) id through func_0203b9fc against the thing at +0x388.
 *
 * `(short)id` is the ROM's `lsl #0x10 ; asr #0x10` sign-extend, so the parameter really is a signed
 * 16-bit value widened at the call -- not an int the compiler happened to truncate. (Declaring the
 * param `short` outright is NOT the same thing and loses 4 bytes.)
 *
 * Shape family of 3: ov212_020ce0d4 / ov266_020cfecc / ov267_020d1cec. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern void func_0203b9fc(int a, int b, int c);
extern VecFx32 data_02041dc8;

void func_ov212_020ce0d4(int obj, int id) {
    *(int *)(obj + 0x5dc) = 0;
    *(signed char *)(obj + 0x5e0) = 0;
    *(signed char *)(obj + 0x5e1) = 0;
    *(VecFx32 *)(obj + 0x4e4) = data_02041dc8;
    func_0203b9fc(*(int *)(obj + 0x388), 0, (short)id);
}
