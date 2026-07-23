/* func_ov267_020d10a4 -- push the current stance byte out to the sub-object's state channels.
 *
 * Stances 0..2 drive channels 2 and 4; anything else drives channel 0 with the stance rebased
 * by 3, so the two groups index separate tables. func_0203c7ac(sub, 0) then closes the update.
 *
 * One of a 3-member shape family; the twins live in ov212/ov266.
 *
 * Four things are load-bearing and each was checked against the disassembly, not the decompiler:
 *  - it is a SWITCH, not an `||` chain. Written as `s == 0 || s == 1 || s == 2` mwcc range-folds
 *    the test into `and #0xff ; cmp #2 ; bhi`; the switch keeps the ROM's `cmp #0 ; cmpne #1 ;
 *    cmpne #2 ; bne`.
 *  - nothing is cached in a local pointer. The stance is at +0x310, past ldrsb's 8-bit immediate,
 *    so the ROM rebuilds `add rN, obj, #0x300` before every `ldrsb [rN, #0x10]`; binding it to a
 *    local instead keeps one pointer live and loses that split.
 *  - func_0203b9fc's 3rd parameter is `short`. That single word IS the default branch's
 *    `lsl #0x10 ; asr #0x10`, and it costs nothing in the other branch because `ldrsb` has
 *    already sign-extended. func_0203c7ac takes two arguments; the ROM sets up r0/r1 only.
 *  - the flag at +0x311 is a bitfield read, not `& 1`: the ROM's `lsl #0x1f ; lsr #0x1f` is the
 *    bit-0 extract. A narrowing cast or a flat mask folds to `and #1`.
 */

typedef struct {
    unsigned char b0 : 1;
    unsigned char rest : 7;
} StanceFlags;

extern void func_0203b9fc(void *sub, int channel, short value, int flag);
extern void func_0203c7ac(void *sub, int a);

void func_ov267_020d10a4(int obj) {
    switch (*(signed char *)(obj + 0x310)) {
    case 0:
    case 1:
    case 2:
        func_0203b9fc(*(void **)(obj + 0x384), 2, *(signed char *)(obj + 0x310),
                      ((StanceFlags *)(obj + 0x311))->b0);
        func_0203b9fc(*(void **)(obj + 0x384), 4, *(signed char *)(obj + 0x310),
                      ((StanceFlags *)(obj + 0x311))->b0);
        break;
    default:
        func_0203b9fc(*(void **)(obj + 0x384), 0, *(signed char *)(obj + 0x310) - 3,
                      ((StanceFlags *)(obj + 0x311))->b0);
        break;
    }
    func_0203c7ac(*(void **)(obj + 0x384), 0);
}
