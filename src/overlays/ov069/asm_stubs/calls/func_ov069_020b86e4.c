extern void data_0204be18(void);

asm void func_ov069_020b86e4(void)
{
    ldr     r1, [pc, #0x14]
    ldr     r0, [pc, #0x18]
    ldr     r2, [r1, #0]
    mov     r3, #0
    strh    r3, [r2, r0]
    ldr     r2, [r1, #0]
    ldrh    r1, [r2, r0]
    sub     r0, r0, #2
    strh    r1, [r2, r0]
    mov     r0, #1
    bx      lr
    mov     r8, r8
    dcd     data_0204be18
    add     r6, r5, r5
    lsl     r0, r0, #0
}
