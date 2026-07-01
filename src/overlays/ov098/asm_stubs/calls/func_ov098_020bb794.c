extern void VEC_Add(void);
extern void func_01ff8e94(void);
extern void func_02030788(void);
extern void func_02033d0c(void);
extern void func_ov022_020914a0(void);
extern void func_ov022_0209198c(void);
extern void func_ov022_02091b48(void);
extern void func_ov022_02091e08(void);
extern void func_ov098_020bb9c4(void);

asm void func_ov098_020bb794(void)
{
    stmfd   sp!, {r4, r5, r6, r7, lr}
    sub     sp, sp, #0x24
    mov     r6, r1
    mov     r7, r0
    ldr     r4, [r7, #8]
    ldr     r5, [r6, #0x138]
    add     ip, sp, #0
    add     r0, r6, #0xcc
    mov     r3, r2
    ldmia   r0, {r0, r1, r2}
    stmia   ip, {r0, r1, r2}
    add     r0, sp, #0xc
    mov     r1, r7
    mov     r2, r6
    bl      func_ov022_0209198c
    mov     r0, r7
    mov     r1, r6
    add     r2, sp, #0
    add     r3, sp, #0xc
    bl      func_ov022_02091b48
    add     r0, sp, #0
    add     r1, sp, #0xc
    add     r2, sp, #0x18
    bl      VEC_Add
    add     r0, sp, #0x18
    add     r3, r6, #0xcc
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    add     r0, sp, #0
    add     r1, sp, #0xc
    bl      func_ov098_020bb9c4
    ldrsb   r0, [r6, #2]
    cmp     r0, #3
    beq     _L_00a4
    add     r1, sp, #0x18
    add     r0, r6, #0x10
    bl      func_01ff8e94
    ldr     r1, [r5, #0x14]
    cmp     r0, r1
    movgt   r0, #4
    strgtb  r0, [r6, #2]
_L_00a4:
    mov     r0, r7
    mov     r1, r6
    bl      func_ov022_02091e08
    ldrb    r0, [r6]
    tst     r0, #1
    beq     _L_00d0
    ldr     r1, [r6, #4]
    ldr     r0, [r5, #0x18]
    cmp     r1, r0
    movge   r0, #4
    strgeb  r0, [r6, #2]
_L_00d0:
    ldrsb   r0, [r6, #2]
    cmp     r0, #2
    beq     _L_0158
    ldrb    r0, [r4, #0x694]
    mov     r0, r0, lsl #0x1f
    movs    r0, r0, lsr #0x1f
    beq     _L_0100
    add     r2, sp, #0x18
    mov     r0, #0xc7
    mov     r1, #1
    mov     r3, #0
    bl      func_02033d0c
_L_0100:
    mov     r0, #4
    strb    r0, [r6, #2]
    mov     r0, #0x2080
    str     r0, [r6, #0xc]
    mov     r2, #0
    mvn     r1, #0
_L_0118:
    add     r0, r6, r2, lsl #1
    add     r0, r0, #0x100
    add     r2, r2, #1
    strh    r1, [r0, #0x3c]
    cmp     r2, #8
    blt     _L_0118
    ldr     r1, [r5, #0x3c]
    mov     r0, r6
    bl      func_ov022_020914a0
    bl      func_02030788
    cmp     r0, #0
    bne     _L_0158
    mov     r0, #3
    strb    r0, [r4, #0x47a]
    mov     r0, #1
    strb    r0, [r4, #0x47b]
_L_0158:
    mov     r0, #0
    add     sp, sp, #0x24
    ldmfd   sp!, {r4, r5, r6, r7, pc}
}
