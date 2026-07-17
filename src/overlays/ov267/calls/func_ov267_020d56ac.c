/* func_ov267_020d56ac -- notify the owner's callback, then run the finaliser if we are in state 1.
 *
 * One of a 3-member shape family; the twins live in ov212/ov266 and are byte-identical modulo
 * relocs (matched here, fanned out with dedupprop).
 *
 * The gate at +0x40 is a SIGNED 1-bit bitfield at bit 1: the ROM's `lsl #0x1e ; asrs #0x1f` sign-
 * extends it, so the extracted value is 0 or -1 and the `asrs` doubles as the test. An `& 2` mask
 * would emit `tst`/`and` instead. See codegen-cracks.md.
 *
 * With that bit set and a callback present at +0xc, the callback is invoked as fp(obj, 0). Then,
 * independently of any of that, state 1 at +0x50 runs func_ov267_020d5884 over +0x214. */

typedef struct {
    int b0 : 1;
    int b1 : 1;
    int rest : 30;
} Bits32;

extern void func_ov267_020d5884(int a);

void func_ov267_020d56ac(int obj) {
    /* The callback must be READ INSIDE the short-circuit, not hoisted into a local: the ROM's
     * `ldrne r2, [r4, #0xc]` only loads it when the gate bit is set. A local makes mwcc load it
     * unconditionally before the test. */
    if (((Bits32 *)(obj + 0x40))->b1 != 0 && *(void (**)(int, int))(obj + 0xc) != 0) {
        (*(void (**)(int, int))(obj + 0xc))(obj, 0);
    }
    if (*(int *)(obj + 0x50) == 1) {
        func_ov267_020d5884(*(int *)(obj + 0x214));
    }
}
