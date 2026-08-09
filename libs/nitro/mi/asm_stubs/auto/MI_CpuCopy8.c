typedef unsigned int u32;

/* NitroSDK alignment-aware byte-copy primitive. */
asm void MI_CpuCopy8(register const void *source, register void *destination,
                     register u32 size)
{
    cmp     r2, #0
    bxeq    lr
    tst     r1, #1
    beq     destinationHalfwordAligned
    ldrh    r12, [r1, #-1]
    and     r12, r12, #0xff
    tst     r0, #1
    ldrneh  r3, [r0, #-1]
    movne   r3, r3, lsr #8
    ldreqh  r3, [r0]
    orr     r3, r12, r3, lsl #8
    strh    r3, [r1, #-1]
    add     r0, r0, #1
    add     r1, r1, #1
    subs    r2, r2, #1
    bxeq    lr
destinationHalfwordAligned:
    eor     r12, r1, r0
    tst     r12, #1
    beq     equalHalfwordAlignment

    bic     r0, r0, #1
    ldrh    r12, [r0], #2
    mov     r3, r12, lsr #8
    subs    r2, r2, #2
    bcc     byteSkewTail
copyByteSkewHalfword:
    ldrh    r12, [r0], #2
    orr     r12, r3, r12, lsl #8
    strh    r12, [r1], #2
    mov     r3, r12, lsr #16
    subs    r2, r2, #2
    bcs     copyByteSkewHalfword
byteSkewTail:
    tst     r2, #1
    bxeq    lr
    ldrh    r12, [r1]
    and     r12, r12, #0xff00
    orr     r12, r12, r3
    strh    r12, [r1]
    bx      lr

equalHalfwordAlignment:
    tst     r12, #2
    beq     equalWordAlignment
    bics    r3, r2, #1
    beq     copyFinalByte
    sub     r2, r2, r3
    add     r12, r3, r1
copyHalfword:
    ldrh    r3, [r0], #2
    strh    r3, [r1], #2
    cmp     r1, r12
    bcc     copyHalfword
    b       copyFinalByte

equalWordAlignment:
    cmp     r2, #2
    bcc     copyFinalByte
    tst     r1, #2
    beq     destinationWordAligned
    ldrh    r3, [r0], #2
    strh    r3, [r1], #2
    subs    r2, r2, #2
    bxeq    lr
destinationWordAligned:
    bics    r3, r2, #3
    beq     copyFinalHalfword
    sub     r2, r2, r3
    add     r12, r3, r1
copyWord:
    ldr     r3, [r0], #4
    str     r3, [r1], #4
    cmp     r1, r12
    bcc     copyWord
copyFinalHalfword:
    tst     r2, #2
    ldrneh  r3, [r0], #2
    strneh  r3, [r1], #2
copyFinalByte:
    tst     r2, #1
    bxeq    lr
    ldrh    r2, [r1]
    ldrh    r0, [r0]
    and     r2, r2, #0xff00
    and     r0, r0, #0xff
    orr     r0, r2, r0
    strh    r0, [r1]
    bx      lr
}
