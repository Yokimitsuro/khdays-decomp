extern void func_ov070_020b99e8(void);
extern void func_ov022_02091b48(void);
extern void func_ov022_02091540(void);
extern void func_01ff8e94(void);
extern void func_ov022_020914a0(void);
extern void VEC_Add(void);

asm void func_ov070_020b9700(void)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, lr}
    sub     sp, sp, #0x18
    mov     r5, r1
    ldr     r4, [r5, #0x138]
    add     r3, sp, #0xc
    mov     r6, r2
    add     r1, r5, #0xcc
    mov     r7, r0
    ldmia   r1, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    add     r0, sp, #0
    mov     r1, r7
    mov     r2, r5
    mov     r3, r6
    bl      func_ov070_020b99e8
    mov     r0, r7
    mov     r1, r5
    add     r2, sp, #0xc
    add     r3, sp, #0
    bl      func_ov022_02091b48
    mov     r1, r6
    add     r0, r5, #0x28
    bl      func_ov022_02091540
    ldrsb   r0, [r5, #2]
    cmp     r0, #3
    beq     _skip
    add     r1, sp, #0xc
    add     r0, r5, #0x10
    bl      func_01ff8e94
    ldr     r1, [r4, #0x14]
    cmp     r0, r1
    bgt     _set4
    ldr     r1, [r5, #4]
    ldr     r0, [r4, #0x18]
    cmp     r1, r0
    blt     _skip
_set4:
    mov     r0, #4
    strb    r0, [r5, #2]
_skip:
    ldrsb   r0, [r5, #2]
    cmp     r0, #2
    beq     _case2
    mov     r0, #4
    strb    r0, [r5, #2]
    mov     r0, #0x3000
    str     r0, [r5, #4]
    mov     r2, #0
    mvn     r1, #0
_clr_loop:
    add     r0, r5, r2, lsl #1
    add     r0, r0, #0x100
    add     r2, r2, #1
    strh    r1, [r0, #0x3c]
    cmp     r2, #8
    blt     _clr_loop
    ldr     r1, [r4, #0x3c]
    mov     r0, r5
    bl      func_ov022_020914a0
    b       _end
_case2:
    add     r0, sp, #0xc
    add     r1, sp, #0
    mov     r2, r0
    bl      VEC_Add
    add     r0, sp, #0xc
    add     r3, r5, #0xcc
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
_end:
    mov     r0, #0
    add     sp, sp, #0x18
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
}
