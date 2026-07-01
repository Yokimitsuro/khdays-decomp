extern int func_0202af2c(void *r0);
extern int func_0202af1c(void *r0);

asm void func_ov020_0207fb8c(void *r0, int r1)
{
    stmfd   sp!, {r3, lr}
    cmp     r1, #0
    ldr     r2, [r0, #8]
    beq     _case0
    cmp     r1, #1
    beq     _case1
    cmp     r1, #2
    ldmfd   sp!, {r3, pc}
_case0:
    ldrsb   r1, [r2, #0x58]
    cmp     r1, #0
    ldmeqfd sp!, {r3, pc}
    add     r0, r0, #0x1c
    bl      func_0202af2c
    ldmfd   sp!, {r3, pc}
_case1:
    ldrsb   r1, [r2, #0x58]
    cmp     r1, #0
    ldmeqfd sp!, {r3, pc}
    add     r0, r0, #0x1c
    bl      func_0202af1c
    ldmfd   sp!, {r3, pc}
}
