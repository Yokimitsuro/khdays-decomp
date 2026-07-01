extern void func_ov028_0208ab20(void);
extern void DC_FlushRange(void);
extern void IC_InvalidateRange(void);

asm void func_ov028_0208a8ac(void *r0)
{
    stmfd   sp!, {r4, r5, r6, lr}
    sub     sp, sp, #0x10
    mov     r4, r0
    ldr     r1, [r4, #4]
    ldr     r6, [pc, #0xcc]
    add     r2, sp, #0
    mov     r0, #0
    mov     lr, #0xf
_L_loop1:
    smull   r3, ip, r6, r0
    mov     r5, r0, lsr #0x1f
    add     ip, r0, ip
    add     ip, r5, ip, asr #3
    smull   ip, r3, lr, ip
    rsb     r3, r5, r0, lsl #30
    add     r3, r5, r3, ror #30
    mov     r3, r3, lsl #3
    mov     r3, r1, lsr r3
    subs    ip, r0, ip
    strb    r3, [r2]
    ldreqb  r3, [r2]
    add     r0, r0, #1
    eoreq   r3, r3, #0xff
    streqb  r3, [r2]
    cmp     r0, #0x10
    add     r2, r2, #1
    blt     _L_loop1
    ldr     r0, [r4]
    cmp     r0, r1
    beq     _L_found1
_L_search1:
    ldr     r0, [r4, #-4]!
    cmp     r0, r1
    bne     _L_search1
_L_found1:
    ldr     r0, [r4, #4]
    mov     r5, #0
    cmp     r1, r0
    beq     _L_found2
_L_search2:
    add     r5, r5, #1
    add     r0, r4, r5, lsl #2
    ldr     r0, [r0, #4]
    cmp     r1, r0
    bne     _L_search2
_L_found2:
    cmp     r5, #0
    beq     _L_skip
    add     r1, r4, #4
    add     r0, sp, #0
    mov     r2, r1
    mov     r3, r5, lsl #2
    bl      func_ov028_0208ab20
_L_skip:
    mov     r5, r5, lsl #2
    mov     r1, r5
    add     r0, r4, #4
    bl      DC_FlushRange
    mov     r1, r5
    add     r0, r4, #4
    bl      IC_InvalidateRange
    add     sp, sp, #0x10
    ldmfd   sp!, {r4, r5, r6, pc}
    dcd     0x88888889
}
