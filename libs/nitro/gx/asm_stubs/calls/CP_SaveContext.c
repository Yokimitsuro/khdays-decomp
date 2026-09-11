/* NitroSDK CP_SaveContext: hand-written ARM, not compiled from C. Saves the
 * geometry coprocessor's divide/sqrt hardware registers (DIVCNT, DIV_NUMER,
 * DIV_DENOM, SQRTCNT, SQRT_PARAM at 0x04000280-0x040002bc) plus two derived
 * mode bits into the caller's context buffer.
 *
 * Confirmed hand-written, not a missed compiler lever: a ROM-wide scan for
 * this exact {r2,r3,r4,ip} block-transfer with r0/r1 pinned as base pointers
 * (no register evicted to lr/ip the way mwcc always does under the same
 * register pressure) finds it in exactly seven places in the whole disc. Six
 * are already-known hand-written asm_stubs siblings (e.g. MTX_Copy43To44_.c);
 * this function is the seventh. A forced compiler probe under matching
 * register pressure picks {r2,r3,ip,lr} + push/pop{lr} every time, on every
 * installed compiler version. */
asm void CP_SaveContext(void *pContext)
{
    ldr     r1, =0x04000290
    stmdb   sp!, {r4}
    ldmia   r1, {r2, r3, r4, ip}
    stmia   r0!, {r2, r3, r4, ip}
    ldrh    ip, [r1, #-0x10]
    add     r1, r1, #0x28
    ldmia   r1, {r2, r3}
    stmia   r0!, {r2, r3}
    and     ip, ip, #3
    ldrh    r2, [r1, #-8]
    strh    ip, [r0]
    and     r2, r2, #1
    strh    r2, [r0, #2]
    ldmia   sp!, {r4}
    bx      lr
}
