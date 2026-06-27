asm void func_ov241_020d0c5c(void *r0)
{
    stmfd   sp!, {r3, lr}
    ldr     r0, [r0, #4]
    ldr     r1, [r0]
    ldr     r2, [r1, #0x3b4]
    cmp     r2, #0
    ldmeqfd sp!, {r3, pc}
    ldr     r0, [r0, #0x30]
    ldrb    r0, [r0, #0x1b4]
    blx     r2
    ldmfd   sp!, {r3, pc}
}
