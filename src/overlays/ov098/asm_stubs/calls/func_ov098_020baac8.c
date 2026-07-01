extern void func_0202aee0(void *r0, int r1);
extern int func_ov022_02083f90(void);
extern void func_ov022_0209145c(void *r0, int r1);
extern void func_ov022_02091474(void *r0);
extern int func_ov022_020912d8(void *r0);
extern int func_02030788(void);
extern void func_ov022_020a4490(void *r0, int r1, int r2);
extern void func_ov022_020ad588(void *r0);

asm void func_ov098_020baac8(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldr     r0, [r4, #0x20]
    mov     r1, #0
    add     r0, r0, #4
    bl      func_0202aee0
    bl      func_ov022_02083f90
    add     r2, r4, #0x2000
    mov     r1, r0
    ldr     r0, [r2, #0x644]
    bl      func_ov022_0209145c
    bl      func_ov022_02083f90
    add     r1, r4, #0x2000
    ldr     r2, [r1, #0x644]
    mov     r1, r0
    add     r0, r2, #0x30
    bl      func_ov022_0209145c
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    bl      func_ov022_02091474
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    add     r0, r0, #0x30
    bl      func_ov022_02091474
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    bl      func_ov022_020912d8
    cmp     r0, #0
    beq     _L_blkA
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    add     r0, r0, #0x30
    bl      func_ov022_020912d8
    cmp     r0, #0
    bne     _L_after
_L_blkA:
    bl      func_02030788
    cmp     r0, #0
    bne     _L_blkB
    add     r0, r4, #0x64
    ldr     r2, [r4, #0x464]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r4, #0x464]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_L_blkB:
    bl      func_02030788
    cmp     r0, #0
    bne     _L_after
    add     r0, r4, #0x6c
    ldr     r2, [r4, #0x46c]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r4, #0x46c]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_L_after:
    ldr     r0, [r4, #0x6bc]
    cmp     r0, #0x2f
    beq     _L_2f
    cmp     r0, #0x30
    beq     _L_30
    b       _L_final
_L_2f:
    ldr     r0, [r4, #0x7b0]
    cmp     r0, #0xf000
    bne     _L_final
    mov     r0, r4
    mov     r1, #0xc7
    mov     r2, #2
    bl      func_ov022_020a4490
    b       _L_final
_L_30:
    ldr     r0, [r4, #0x7b0]
    cmp     r0, #0x1b000
    bne     _L_final
    mov     r0, r4
    mov     r1, #0xc7
    mov     r2, #3
    bl      func_ov022_020a4490
_L_final:
    mov     r0, r4
    bl      func_ov022_020ad588
    ldmfd   sp!, {r4, pc}
}
