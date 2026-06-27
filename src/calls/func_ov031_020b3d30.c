extern void func_ov031_020b3a9c(void);
extern void func_ov022_02095524(void);
extern void func_ov031_020b3a00(void);
extern void func_ov022_02095554(void);

asm void func_ov031_020b3d30(void)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, lr}
    mov     r4, r1
    mov     r8, r0
    mov     r7, r2
    add     r6, r4, #0xc
    mov     r5, #0
_loop:
    mov     r0, r8
    mov     r1, r6
    mov     r2, r7
    bl      func_ov031_020b3a9c
    add     r5, r5, #1
    cmp     r5, #2
    add     r6, r6, #0x118
    blt     _loop
    add     r0, r8, #0x2f8
    add     r0, r0, #0x2000
    bl      func_ov022_02095524
    cmp     r0, #0
    ldmeqfd sp!, {r4, r5, r6, r7, r8, pc}
    ldr     r0, [r4, #0x128]
    cmp     r0, #0
    bne     _skip1
    add     r0, r4, #0x124
    bl      func_ov031_020b3a00
_skip1:
    add     r0, r8, #0x2f8
    add     r0, r0, #0x2000
    bl      func_ov022_02095554
    cmp     r0, #0
    ldmeqfd sp!, {r4, r5, r6, r7, r8, pc}
    ldr     r0, [r4, #0x10]
    cmp     r0, #0
    ldmnefd sp!, {r4, r5, r6, r7, r8, pc}
    add     r0, r4, #0xc
    bl      func_ov031_020b3a00
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
}
