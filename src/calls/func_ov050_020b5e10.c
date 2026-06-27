extern void func_ov022_02083f90(void);
extern void func_ov022_0209145c(void);
extern void func_ov022_02091474(void);
extern void func_ov022_020912d8(void);
extern void func_02030788(void);
extern void func_ov022_020ad588(void);

asm void func_ov050_020b5e10(void)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
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
    bl      func_ov022_02083f90
    add     r1, r4, #0x2000
    ldr     r2, [r1, #0x644]
    mov     r1, r0
    add     r0, r2, #0x60
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
    add     r0, r0, #0x60
    bl      func_ov022_02091474
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    bl      func_ov022_020912d8
    cmp     r0, #0
    beq     _bcheck
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    add     r0, r0, #0x30
    bl      func_ov022_020912d8
    cmp     r0, #0
    beq     _bcheck
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    add     r0, r0, #0x60
    bl      func_ov022_020912d8
    cmp     r0, #0
    bne     _last
_bcheck:
    bl      func_02030788
    cmp     r0, #0
    bne     _skip1
    add     r0, r4, #0x64
    ldr     r2, [r4, #0x464]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r4, #0x464]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_skip1:
    bl      func_02030788
    cmp     r0, #0
    bne     _last
    add     r0, r4, #0x6c
    ldr     r2, [r4, #0x46c]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r4, #0x46c]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_last:
    mov     r0, r4
    bl      func_ov022_020ad588
    ldmfd   sp!, {r4, pc}
}
