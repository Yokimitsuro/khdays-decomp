extern void func_02016b60(void);
extern void func_ov022_02091eb0(void);

asm void func_ov064_020b7100(void)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, lr}
    mov     r6, r0
    ldrb    r0, [r6, #0x19]
    mov     r4, #0
    cmp     r0, #0
    ldmlefd sp!, {r4, r5, r6, r7, r8, pc}
    mov     r5, r4
    mov     r7, #2
_loop:
    ldr     r0, [r6, #0xc]
    add     r8, r0, r5
    ldrsb   r0, [r8, #2]
    cmp     r0, #0
    cmpne   r0, #3
    beq     _skip
    ldr     r0, [r8, #0xa0]
    mov     r1, r7
    rsb     r2, r4, #0x1c
    bl      func_02016b60
    mov     r0, r8
    bl      func_ov022_02091eb0
_skip:
    ldrb    r0, [r6, #0x19]
    add     r4, r4, #1
    add     r5, r5, #0x1c8
    cmp     r4, r0
    blt     _loop
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
}
