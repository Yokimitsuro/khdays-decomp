typedef unsigned int u32;

/* NitroSDK alignment-aware byte-fill primitive. */
asm void MI_CpuFill8(register void *destination, register u32 value,
                     register u32 size)
{
    cmp     r2, #0
    bxeq    lr
    tst     r0, #1
    beq     destinationHalfwordAligned
    ldrh    r12, [r0, #-1]
    and     r12, r12, #0xff
    orr     r3, r12, r1, lsl #8
    strh    r3, [r0, #-1]
    add     r0, r0, #1
    subs    r2, r2, #1
    bxeq    lr
destinationHalfwordAligned:
    cmp     r2, #2
    bcc     fillFinalByte
    orr     r1, r1, r1, lsl #8
    tst     r0, #2
    beq     destinationWordAligned
    strh    r1, [r0], #2
    subs    r2, r2, #2
    bxeq    lr
destinationWordAligned:
    orr     r1, r1, r1, lsl #16
    bics    r3, r2, #3
    beq     fillFinalHalfword
    sub     r2, r2, r3
    add     r12, r3, r0
fillNextWord:
    str     r1, [r0], #4
    cmp     r0, r12
    bcc     fillNextWord
fillFinalHalfword:
    tst     r2, #2
    strneh  r1, [r0], #2
fillFinalByte:
    tst     r2, #1
    bxeq    lr
    ldrh    r3, [r0]
    and     r3, r3, #0xff00
    and     r1, r1, #0xff
    orr     r1, r1, r3
    strh    r1, [r0]
    bx      lr
}
