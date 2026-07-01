extern void func_0203c5c0(void);
extern void func_ov241_020d04a0(void);

asm void func_ov241_020d0170(void *r0)
{
    stmfd   sp!, {r3, r4, lr}
    sub     sp, sp, #0xc
    mov     r2, #0
    str     r2, [sp]
    add     r1, sp, #8
    str     r1, [sp, #4]
    mov     r4, r0
    ldr     r0, [r4, #0x3c]
    ldr     r3, =func_ov241_020d04a0
    mov     r1, #0x64
    mov     r2, #0x44
    bl      func_0203c5c0
    ldr     r0, [sp, #8]
    str     r4, [r0]
    ldr     r0, [sp, #8]
    str     r0, [r4, #0x214]
    add     sp, sp, #0xc
    ldmfd   sp!, {r3, r4, pc}
}
