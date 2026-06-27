extern void func_ov022_0209198c(void);
extern void func_ov022_02091b48(void);
extern void VEC_Add(void);
extern void func_ov022_02091540(void);
extern void func_01ff8e94(void);
extern void func_ov022_02091e08(void);
extern void func_02033d0c(void);
extern void func_ov070_020b98e8(void);
extern void func_02030788(void);
extern void func_ov022_020914a0(void);

asm void func_ov070_020b9574(void)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, lr}
    sub     sp, sp, #0x18
    mov     r7, r1
    mov     r8, r0
    ldr     r4, [r8, #8]
    ldr     r5, [r7, #0x138]
    mov     r6, r2
    add     r0, r7, #0xcc
    add     r3, sp, #0xc
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    add     r0, sp, #0
    mov     r1, r8
    mov     r2, r7
    mov     r3, r6
    bl      func_ov022_0209198c
    mov     r0, r8
    mov     r1, r7
    add     r2, sp, #0xc
    add     r3, sp, #0
    bl      func_ov022_02091b48
    add     r0, sp, #0xc
    add     r1, sp, #0
    mov     r2, r0
    bl      VEC_Add
    add     r0, sp, #0xc
    add     r3, r7, #0xcc
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r1, r6
    add     r0, r7, #0x28
    bl      func_ov022_02091540
    ldrsb   r0, [r7, #2]
    cmp     r0, #3
    beq     _afterA
    add     r1, sp, #0xc
    add     r0, r7, #0x10
    bl      func_01ff8e94
    ldr     r1, [r5, #0x14]
    cmp     r0, r1
    movgt   r0, #4
    strgtb  r0, [r7, #2]
_afterA:
    mov     r0, r8
    mov     r1, r7
    bl      func_ov022_02091e08
    ldrb    r0, [r7]
    tst     r0, #1
    beq     _afterB
    ldr     r1, [r7, #4]
    ldr     r0, [r5, #0x18]
    cmp     r1, r0
    movge   r0, #4
    strgeb  r0, [r7, #2]
_afterB:
    ldrsb   r0, [r7, #2]
    cmp     r0, #2
    beq     _end
    ldr     r0, [r8]
    cmp     r0, #1
    bne     _set4
    ldrb    r0, [r4, #0x694]
    mov     r0, r0, lsl #0x1f
    movs    r0, r0, lsr #0x1f
    beq     _skipDbg
    add     r2, sp, #0xc
    mov     r0, #0xcb
    mov     r1, #1
    mov     r3, #0
    bl      func_02033d0c
_skipDbg:
    add     r0, sp, #0xc
    add     r1, sp, #0
    bl      func_ov070_020b98e8
    bl      func_02030788
    cmp     r0, #0
    bne     _set4
    ldr     r0, [r4]
    tst     r0, #0x10000
    bne     _set4
    mov     r0, #3
    strb    r0, [r4, #0x47a]
    mov     r0, #1
    strb    r0, [r4, #0x47b]
_set4:
    mov     r0, #4
    strb    r0, [r7, #2]
    mov     r0, #0x3000
    str     r0, [r7, #4]
    mov     r2, #0
    mvn     r1, #0
_loop:
    add     r0, r7, r2, lsl #1
    add     r0, r0, #0x100
    add     r2, r2, #1
    strh    r1, [r0, #0x3c]
    cmp     r2, #8
    blt     _loop
    ldr     r1, [r5, #0x3c]
    mov     r0, r7
    bl      func_ov022_020914a0
_end:
    mov     r0, #0
    add     sp, sp, #0x18
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
}
