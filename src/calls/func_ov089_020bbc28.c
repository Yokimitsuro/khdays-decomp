extern void func_0202accc(void);
extern void func_01fff774(void);

asm void func_ov089_020bbc28(void)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r1
    ldr     r0, [r4]
    cmp     r0, #0
    ldmnefd sp!, {r4, pc}
    mov     r1, #0
    mov     r3, r1
    add     r0, r4, #0xc
    add     r2, r4, #0xec
    bl      func_0202accc
    add     r0, r4, #0xc
    add     r2, r4, #0xec
    mov     r1, #2
    mov     r3, #0
    bl      func_0202accc
    mov     r1, #0
    mov     r2, r1
    add     r0, r4, #0xc
    bl      func_01fff774
    add     r0, r4, #0xc
    mov     r1, #2
    mov     r2, #0
    bl      func_01fff774
    mov     r0, #1
    str     r0, [r4]
    ldmfd   sp!, {r4, pc}
}
