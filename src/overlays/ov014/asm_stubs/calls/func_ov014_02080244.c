extern void func_0202a7dc(void *r0);

asm void func_ov014_02080244(void *r0)
{
    stmfd   sp!, {r3, lr}
    ldr     r1, [r0, #8]
    ldrsb   r1, [r1, #0x58]
    cmp     r1, #0
    ldmeqfd sp!, {r3, pc}
    add     r0, r0, #0x2c
    bl      func_0202a7dc
    ldmfd   sp!, {r3, pc}
}
