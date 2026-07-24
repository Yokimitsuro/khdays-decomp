/* func_ov006_0204e35c -- Mission Mode "start" gate.
 *
 * Reports "no handler yet" (null) while the scene is still blocked (+0x49c) and while
 * the ov105 sound/transfer stage has not fired.  Once it fires, hand back the next
 * scene handler; if it reports failure, latch +0x4f0 and stay on null.
 *
 * CODEGEN NOTE -- the ROM materialises the null result ONCE up front (`mov r0,#0`
 * scheduled into the pool load's load-use slot) and runs the guard chain through r1;
 * writing the guard as an early `if (blocked) return null;` makes mwcc compute the
 * chain in r0 and predicate the result with `movne r0,#0` instead.  Two source shapes
 * are load-bearing here:
 *   1. the guard is the POSITIVE form -- `if (!blocked) { ... }` wrapping the body,
 *      with a single `return next;` at the end;
 *   2. the failure path RE-ASSIGNS `next = 0;`.  It is redundant as C, but it is what
 *      forces mwcc to emit the second `mov r0,#0` in the tail; drop it and the tail
 *      shares the leading zero and the function is 4 bytes short.
 * Same shape matches its ov008 twin func_ov008_0207a1c4.
 */
typedef struct Ov006MissionCtx {
    char _pad0000[0x49c];
    int nStartBlocked;             /* +0x49c: non-zero while the start is held off */
    char _pad04a0[0x4f0 - 0x49c - 4];
    unsigned char bStartFailed;    /* +0x4f0: latched when the ov105 stage refuses */
} Ov006MissionCtx;

typedef void (*Ov006Handler)(void);

extern Ov006MissionCtx *data_ov006_020565e4;
extern int func_ov105_020bf5a8(void);
extern void func_ov006_0204e300(void);

Ov006Handler func_ov006_0204e35c(void) {
    Ov006Handler next = 0;

    if (data_ov006_020565e4->nStartBlocked == 0) {
        if (func_ov105_020bf5a8() != 0) {
            return &func_ov006_0204e300;
        }
        data_ov006_020565e4->bStartFailed = 1;
        next = 0;
    }
    return next;
}
