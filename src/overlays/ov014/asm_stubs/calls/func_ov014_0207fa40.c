extern void func_ov002_0207c618(void *r0, int r1, int r2);
extern void func_0202af1c(void *r0);

asm void func_ov014_0207fa40(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldrb    r0, [r4, #0x1b1]
    orr     r0, r0, #2
    strb    r0, [r4, #0x1b1]
    ldrh    r0, [r4, #0x12]
    tst     r0, #4
    ldmeqfd sp!, {r4, pc}
    add     r0, r4, #0x3c
    mov     r2, #0
    bl      func_ov002_0207c618
    add     r0, r4, #0x3c
    bl      func_0202af1c
    ldmfd   sp!, {r4, pc}
}
