/* func_ov024_02082e04 -- MobiClip: post a stop request of the given kind to the active player.
 * The request itself is always recorded (payload at +0xbe4, result slot at +0xbe8 primed to -1,
 * kind at +0xbe2); what differs is which slots get woken. Kind 0 touches the audio-side slot
 * (state at +0xbd8), kind 1 the video-side slot (+0xbdc), kind 2 both. A slot is only moved to
 * state 2 and kicked if it is currently in state 1 -- except the video slot under kind 1, which is
 * kicked unconditionally. Any other kind just records the request.
 * The kick side (func_ov024_02084df4) takes 1 for the audio slot and 0 for the video slot.
 * player == data_ov024_02093a20[1], the same active-player global func_ov024_02082a28 reads.
 *
 * NONMATCHING: 180/180 bytes, byte-exact through 0x8c (out of 0xb0). The only difference is an
 * r1/r2 swap in the LAST block: after the kick call the ROM rematerialises the control base into
 * r1 and puts the constant 2 in r2 (`add r1,r4,#0x8000 ... mov r2,#2 ; str r2,[r1,#0xbdc]`),
 * while mwcc mirrors the pair. Every earlier block agrees exactly (base r2, value r1).
 * Tried and rejected: a second base local for the block, and swapping the two locals' decl order.
 * Same diff at 0x8d -- the regalloc-permutation class (see deferred-ties.md).
 *
 * ★ Two knobs here DID matter and must be kept if anyone retries this:
 * 1. `ctl` must be a separate local for the base (player + 0x8000). Folding it into one constant
 *    offset -- *(int *)(player + 0x8bd8) -- makes mwcc materialise the full address for every
 *    STORE (add #0x3d8 ; add #0x8800 ; str [r,#0]) while still folding the LOADS correctly.
 *    That is +24 bytes.
 * 2. `ctl` must be a POINTER (char *), not an int holding the address. As an int it still splits
 *    the stores (add #0x3d8 ; str [r,#0x800]), +12 bytes. Only the pointer type gets the ROM's
 *    single `str r1,[r2,#0xbd8]`.
 * So: right size and shape need both; what is left over is purely the one register pair.
 */
extern void func_ov024_02084df4(int which);
extern int data_ov024_02093a20[];

void func_ov024_02082e04(int kind, int arg) {
    int player;
    char *ctl;

    player = data_ov024_02093a20[1];
    ctl = (char *)(player + 0x8000);
    *(int *)(ctl + 0xbe4) = arg;
    *(int *)(ctl + 0xbe8) = -1;
    *(unsigned char *)(ctl + 0xbe2) = (unsigned char)kind;

    switch (kind) {
    case 0:
        if (*(int *)(ctl + 0xbd8) == 1) {
            *(int *)(ctl + 0xbd8) = 2;
            func_ov024_02084df4(1);
        }
        break;
    case 1:
        *(int *)(ctl + 0xbdc) = 2;
        func_ov024_02084df4(0);
        break;
    case 2:
        if (*(int *)(ctl + 0xbd8) == 1) {
            *(int *)(ctl + 0xbd8) = 2;
            func_ov024_02084df4(1);
        }
        if (*(int *)(ctl + 0xbdc) == 1) {
            *(int *)(ctl + 0xbdc) = 2;
            func_ov024_02084df4(0);
        }
        break;
    }
}
