/* func_ov008_0207a1c4 -- card-transfer "begin" gate.
 *
 * While the owner is busy (+0x49c) there is no follow-up handler.  Otherwise ask the
 * ov105 stage to start the transfer: on success hand back the follow-up handler, on
 * failure latch +0x4f0 and stay on null.
 *
 * CODEGEN NOTE -- see the twin func_ov006_0204e35c.  The ROM materialises the null
 * result up front (`mov r0,#0` filling the pool load's load-use slot) and runs the busy
 * chain through r1.  Writing the guard as an early `if (busy) return 0;` makes mwcc run
 * the chain through r0 and predicate the result with `movne r0,#0`.  The positive guard
 * plus the redundant `next = 0;` on the failure path is what reproduces the ROM: without
 * that re-assignment the tail shares the leading zero and the function is 4 bytes short.
 */
typedef struct CardXferOwner {
    char _pad0000[0x49c];
    int nBusy;                     /* +0x49c: a transfer is already in flight */
    char _pad04a0[0x4f0 - 0x49c - 4];
    unsigned char bStartFailed;    /* +0x4f0: latched when the start is refused */
} CardXferOwner;

typedef void (*Ov008Handler)(void);

extern CardXferOwner *data_ov008_02090f24;
extern int func_ov105_020bf5a8(void);
extern void func_ov008_0207a168(void);

Ov008Handler func_ov008_0207a1c4(void) {
    Ov008Handler next = 0;

    if (data_ov008_02090f24->nBusy == 0) {
        if (func_ov105_020bf5a8() != 0) {
            return &func_ov008_0207a168;
        }
        data_ov008_02090f24->bStartFailed = 1;
        next = 0;
    }
    return next;
}
