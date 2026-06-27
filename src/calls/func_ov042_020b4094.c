extern void func_ov042_020b41f4(void *r0, void *r1, void *r2);
extern void func_ov022_020916e8(void *r0, void *r1, void *r2);
extern void func_02033d0c(int r0, int r1, void *r2, int r3);
extern int func_02030788(void);
extern char data_ov042_020b4754[];

asm void func_ov042_020b4094(void *r0, void *r1)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    mov     r10, r0
    ldrb    r0, [r10, #0x19]
    mov     r5, #0
    ldr     r6, [r10, #8]
    mov     r9, r1
    mov     r7, r5
    cmp     r0, #0
    ldmlefd sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
    ldr     r11, [pc, #0xdc]
    mov     r8, r5
_L_loop:
    ldr     r0, [r10, #0xc]
    add     r4, r0, r8
    ldrsb   r0, [r4, #2]
    cmp     r0, #0
    beq     _L_iter
    cmp     r0, #2
    beq     _L_eq2
    mov     r1, r4
    ldr     r3, [r11, r0, lsl #2]
    mov     r0, r10
    mov     r2, r9
    blx     r3
    b       _L_iter
_L_eq2:
    ldr     r0, [r10]
    cmp     r0, #1
    bne     _L_neq1
    mov     r1, r4
    mov     r0, r10
    mov     r2, r9
    bl      func_ov042_020b41f4
    b       _L_iter
_L_neq1:
    mov     r0, r10
    mov     r1, r4
    mov     r2, r9
    bl      func_ov022_020916e8
    ldrsb   r0, [r4, #2]
    cmp     r0, #4
    cmpeq   r5, #0
    bne     _L_iter
    ldrb    r0, [r6, #0x694]
    mov     r0, r0, lsl #0x1f
    movs    r0, r0, lsr #0x1f
    beq     _L_skip1
    mov     r1, #0
    mov     r0, #0xc7
    add     r2, r4, #0xcc
    mov     r3, r1
    bl      func_02033d0c
_L_skip1:
    mov     r5, #1
    bl      func_02030788
    cmp     r0, #0
    bne     _L_iter
    ldr     r1, [r6]
    tst     r1, #0x10000
    bne     _L_iter
    mov     r0, #3
    strb    r0, [r6, #0x47a]
    mov     r0, #0
    strb    r0, [r6, #0x47b]
_L_iter:
    ldrb    r0, [r10, #0x19]
    add     r8, r8, #0x1c8
    add     r7, r7, #1
    cmp     r7, r0
    blt     _L_loop
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
    dcd     data_ov042_020b4754
}
