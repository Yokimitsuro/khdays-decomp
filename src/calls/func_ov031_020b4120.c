extern void func_02030788(void);
extern void func_ov022_020912d8(void);
extern void func_ov022_020a35f4(void);
extern void *data_ov031_020b4dc0;

asm void func_ov031_020b4120(void)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, lr}
    ldr     r2, =data_ov031_020b4dc0
    mov     r8, r0
    ldr     r0, [r2]
    mov     r7, r1
    add     r0, r0, #0x2c
    add     r4, r0, #0x2c00
    mov     r5, #0
    mov     r6, #1
    bl      func_02030788
    cmp     r0, #0
    bne     _skip1
    add     r0, r8, #0x64
    ldr     r2, [r8, #0x464]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r8, #0x464]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_skip1:
    bl      func_02030788
    cmp     r0, #0
    bne     _skip2
    add     r0, r8, #0x6c
    ldr     r2, [r8, #0x46c]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r8, #0x46c]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_skip2:
    mov     r0, #0
    str     r0, [r4, #4]
    str     r7, [r4]
    cmp     r7, #0
    beq     _z2
    add     r0, r8, #0x2000
    ldr     r0, [r0, #0x644]
    add     r0, r0, #0x30
    bl      func_ov022_020912d8
    cmp     r0, #0
    beq     _z1
    add     r0, r8, #0x2000
    ldr     r0, [r0, #0x644]
    add     r0, r0, #0x60
    bl      func_ov022_020912d8
    cmp     r0, #0
    bne     _z2
_z1:
    mov     r6, #0
_z2:
    cmp     r6, #0
    beq     _end
    mov     r0, r8
    mov     r1, #0x21
    bl      func_ov022_020a35f4
    mov     r5, r0
_end:
    mov     r0, r5
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
}
