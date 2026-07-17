/* func_ov212_020cd494 -- push the current stance byte out to the sub-object's state channels.
 *
 * Stances 0..2 drive channels 2 and 4; anything else drives channel 0 with the stance rebased
 * by 3, so the two groups index separate tables. func_0203c7ac(sub, 0) then closes the update.
 *
 * One of a 3-member shape family; the twins live in ov266/ov267 and are byte-identical modulo
 * relocs (matched here, fanned out with dedupprop).
 *
 * Three things are load-bearing and each was checked against the disassembly, not the decompiler:
 *  - func_0203b9fc's 3rd parameter is `short`. That single word IS the else branch's
 *    `lsl #0x10 ; asr #0x10`, and it costs nothing in the if branch because `ldrsb` has already
 *    sign-extended. Ghidra renders the call with four arguments for func_0203c7ac too -- it takes
 *    two; the ROM sets up r0/r1 only.
 *  - the stance is re-read through the pointer for the second call and NOT cached in a local.
 *    mwcc CSEs the compare chain with the first call, then has to reload across the call because
 *    the callee may have written it -- which is exactly the ROM's shape.
 *  - the flag at +0x311 is a bitfield read, not `& 1`: the ROM's `lsl #0x1f ; lsr #0x1f` is the
 *    bit-0 extract from codegen-cracks.md. A narrowing cast or a flat mask folds to `and #1`.
 */

typedef struct {
    unsigned char b0 : 1;
    unsigned char rest : 7;
} StanceFlags;

extern void func_0203b9fc(void *sub, int channel, short value, int flag);
extern void func_0203c7ac(void *sub, int a);

void func_ov212_020cd494(int obj) {
    signed char *stance = (signed char *)(obj + 0x310);
    StanceFlags *flags = (StanceFlags *)(obj + 0x311);

    if (*stance == 0 || *stance == 1 || *stance == 2) {
        func_0203b9fc(*(void **)(obj + 0x384), 2, *stance, flags->b0);
        func_0203b9fc(*(void **)(obj + 0x384), 4, *stance, flags->b0);
    } else {
        func_0203b9fc(*(void **)(obj + 0x384), 0, *stance - 3, flags->b0);
    }
    func_0203c7ac(*(void **)(obj + 0x384), 0);
}
