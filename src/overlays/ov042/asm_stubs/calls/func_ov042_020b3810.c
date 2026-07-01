extern int func_02030788(void);
extern int func_ov022_02095554(void *r0);
extern int func_ov022_020912d8(void *r0);
extern int func_ov022_020a35f4(void *r0, int r1);
extern char data_ov042_020b4800[];

asm int func_ov042_020b3810(void *r0)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, lr}
    ldr     r1, [pc, #0xb4]
    mov     r7, r0
    ldr     r0, [r1]
    mov     r4, #0
    add     r0, r0, #0x2c
    add     r5, r0, #0x2c00
    mov     r6, #1
    bl      func_02030788
    cmp     r0, #0
    bne     _L_skip1
    add     r0, r7, #0x64
    ldr     r2, [r7, #0x464]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r7, #0x464]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_L_skip1:
    bl      func_02030788
    cmp     r0, #0
    bne     _L_skip2
    add     r0, r7, #0x6c
    ldr     r2, [r7, #0x46c]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r7, #0x46c]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_L_skip2:
    add     r0, r7, #0x2f8
    add     r0, r0, #0x2000
    bl      func_ov022_02095554
    str     r0, [r5, #8]
    cmp     r0, #0
    beq     _L_skip3
    add     r0, r7, #0x2000
    ldr     r0, [r0, #0x644]
    add     r0, r0, #0x30
    bl      func_ov022_020912d8
    cmp     r0, #0
    moveq   r6, #0
_L_skip3:
    cmp     r6, #0
    beq     _L_end
    mov     r0, r7
    mov     r1, #0x21
    bl      func_ov022_020a35f4
    mov     r4, r0
_L_end:
    mov     r0, r4
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
    dcd     data_ov042_020b4800
}
