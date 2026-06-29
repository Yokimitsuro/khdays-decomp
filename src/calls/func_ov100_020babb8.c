
asm void func_ov100_020babb8(void)
{
    ldr     r1, [pc, #0x64]
    ldrb    r0, [r0, r1]
    cmp     r0, #0x17
    bhi     _L_0064
    add     r0, r0, r0
    add     r0, pc
    ldrh    r0, [r0, #6]
    lsl     r0, r0, #0x10
    asr     r0, r0, #0x10
    add     pc, r0
    lsl     r6, r1, #1
    lsl     r6, r1, #1
    lsl     r6, r1, #1
    lsl     r6, r1, #1
    lsl     r6, r1, #1
    lsl     r6, r5, #0
    lsl     r6, r5, #0
    lsl     r2, r6, #0
    lsl     r2, r6, #0
    lsl     r2, r6, #0
    lsl     r2, r6, #0
    lsl     r6, r6, #0
    lsl     r6, r6, #0
    lsl     r6, r6, #0
    lsl     r2, r7, #0
    lsl     r2, r7, #0
    lsl     r6, r7, #0
    lsl     r6, r7, #0
    lsl     r6, r7, #0
    lsl     r6, r7, #0
    lsl     r2, r0, #1
    lsl     r6, r0, #1
    lsl     r2, r1, #1
    lsl     r6, r5, #0
    mov     r0, #0x91
    bx      lr
    mov     r0, #0x92
    bx      lr
    mov     r0, #0x93
    bx      lr
    mov     r0, #0x94
    bx      lr
    mov     r0, #0x95
    bx      lr
    mov     r0, #0x8e
    bx      lr
    mov     r0, #0x8f
    bx      lr
    mov     r0, #0x90
    bx      lr
_L_0064:
    mov     r0, #0x8d
    bx      lr
    dcd     0x00000918
}
