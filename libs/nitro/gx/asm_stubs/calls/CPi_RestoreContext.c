/* NitroSDK CPi_RestoreContext: hand-written ARM, not compiled from C. Mirror
 * of CP_SaveContext.c (read that file's header for the full provenance
 * argument) — restores the geometry coprocessor's divide/sqrt hardware
 * registers (DIVCNT, DIV_NUMER, DIV_DENOM, SQRTCNT, SQRT_PARAM at
 * 0x04000280-0x040002bc) from a previously-saved context buffer. */
asm void CPi_RestoreContext(const void *pContext)
{
    stmdb   sp!, {r4}
    ldr     r1, =0x04000290
    ldmia   r0, {r2, r3, r4, ip}
    stmia   r1, {r2, r3, r4, ip}
    ldrh    r2, [r0, #0x18]
    ldrh    r3, [r0, #0x1a]
    strh    r2, [r1, #-0x10]
    strh    r3, [r1, #0x20]
    add     r0, r0, #0x10
    add     r1, r1, #0x28
    ldmia   r0, {r2, r3}
    stmia   r1, {r2, r3}
    ldmia   sp!, {r4}
    bx      lr
}
