extern void func_ov022_02091324(void);

asm void func_ov068_020b6a7c(void)
{
    stmfd   sp!, {lr}
    sub     sp, sp, #0x2c
    add     r3, sp, #0
    mov     lr, r0
    mov     ip, r1
    ldmia   r2, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r3, #0
    mov     r2, #1
    mov     r1, #0x1000
    mov     r0, #0x2100
    str     r3, [sp, #0x14]
    str     r2, [sp, #0x1c]
    str     r3, [sp, #0x20]
    strh    r3, [sp, #0xc]
    strh    r1, [sp, #0xe]
    strh    r3, [sp, #0x10]
    str     r3, [sp, #0x28]
    str     r3, [sp, #0x24]
    str     r3, [sp, #0x18]
    strh    r0, [sp, #0x12]
    ldr     r0, [ip, #0x118]
    cmp     r0, #0
    beq     _skip
    mov     r0, #0x2480
    str     r2, [sp, #0x28]
    str     r2, [sp, #0x24]
    strh    r0, [sp, #0x12]
    str     r2, [sp, #0x18]
_skip:
    add     r1, sp, #0
    mov     r0, lr
    bl      func_ov022_02091324
    add     sp, sp, #0x2c
    ldmfd   sp!, {pc}
}
