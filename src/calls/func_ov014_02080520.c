extern void func_0202aa9c(void *r0);

asm int func_ov014_02080520(void *r0)
{
    stmfd   sp!, {r3, lr}
    ldrh    r1, [r0, #0x12]
    tst     r1, #4
    beq     _L18
    add     r0, r0, #0x2c
    bl      func_0202aa9c
_L18:
    mov     r0, #0
    ldmfd   sp!, {r3, pc}
}
