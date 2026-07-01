extern int func_ov022_02095554(void *r0);
extern int func_ov022_020ad114(void *r0);
extern void func_ov022_020ad0c0(void *r0);
extern void VEC_Subtract(void *r0, void *r1, void *r2);
extern int VEC_Mag(void *r0);
extern void func_01ff8d18(void *r0, void *r1);
extern int FX_Atan2(int r0, int r1);
extern char func_ov042_020b38d4[];

asm int func_ov042_020b3690(void *r0, int r1)
{
    stmfd   sp!, {r3, r4, r5, r6, lr}
    sub     sp, sp, #0xc
    mov     r5, r0
    cmp     r1, #0x21
    mov     r4, #0
    bne     _L_end
    add     r0, r5, #0x2f8
    add     r1, r5, #0x2c
    add     r0, r0, #0x2000
    add     r6, r1, #0x2c00
    ldr     r4, [pc, #0xc4]
    bl      func_ov022_02095554
    cmp     r0, #0
    ldr     r2, [r5, #0x664]
    mov     r0, r5
    beq     _L_else
    mov     r1, #0x30
    blx     r2
    b       _L_after
_L_else:
    mov     r1, #0x2f
    blx     r2
_L_after:
    mov     r1, #0
    str     r1, [r6, #4]
    str     r1, [r6, #0xc]
    mov     r0, r5
    str     r1, [r6, #0x10]
    bl      func_ov022_020ad114
    cmp     r0, #0
    beq     _L_end
    mov     r0, r5
    bl      func_ov022_020ad0c0
    add     r1, r5, #0x8c
    add     r2, sp, #0
    add     r1, r1, #0x400
    bl      VEC_Subtract
    add     r0, sp, #0
    bl      VEC_Mag
    cmp     r0, #0
    beq     _L_skip
    add     r0, sp, #0
    mov     r1, r0
    bl      func_01ff8d18
_L_skip:
    ldr     r0, [sp]
    ldr     r1, [sp, #8]
    rsb     r0, r0, #0
    rsb     r1, r1, #0
    bl      FX_Atan2
    ldr     r2, [r5, #0x20]
    mov     r0, r0, lsl #0x10
    ldr     r1, [r2]
    mov     r0, r0, lsr #0x10
    tst     r1, #0x20
    bne     _L_end
    add     r0, r0, #0x8000
    strh    r0, [r2, #0x80]
    ldrh    r0, [r2, #4]
    orr     r0, r0, #0x20
    strh    r0, [r2, #4]
_L_end:
    mov     r0, r4
    add     sp, sp, #0xc
    ldmfd   sp!, {r3, r4, r5, r6, pc}
    dcd     func_ov042_020b38d4
}
