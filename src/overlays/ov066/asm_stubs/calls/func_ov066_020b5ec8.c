extern void FX_Atan2(void);
extern void VEC_Mag(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_ov022_020ad0c0(void);
extern void func_ov022_020ad114(void);
extern void func_ov066_020b66d0(void);

asm void func_ov066_020b5ec8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    stmfd   sp!, {r4, r5, lr}
    sub     sp, sp, #0xc
    mov     r5, r0
    add     r2, r5, #0xc50
    cmp     r1, #0x21
    add     r1, r2, #0x2000
    mov     r4, #0
    bne     _L00cc
    ldr     r1, [r1]
    ldr     r4, [pc, #0xac]
    cmp     r1, #0
    ldr     r2, [r5, #0x664]
    beq     _L0040
    mov     r1, #0x31
    blx     r2
    b       _L0048
_L0040:
    mov     r1, #0x30
    blx     r2
_L0048:
    mov     r0, r5
    bl      func_ov022_020ad114
    cmp     r0, #0
    beq     _L00cc
    mov     r0, r5
    bl      func_ov022_020ad0c0
    add     r1, r5, #0x8c
    add     r2, sp, #0
    add     r1, r1, #0x400
    bl      VEC_Subtract
    add     r0, sp, #0
    bl      VEC_Mag
    cmp     r0, #0
    beq     _L008c
    add     r0, sp, #0
    mov     r1, r0
    bl      func_01ff8d18
_L008c:
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
    bne     _L00cc
    add     r0, r0, #0x8000
    strh    r0, [r2, #0x80]
    ldrh    r0, [r2, #4]
    orr     r0, r0, #0x20
    strh    r0, [r2, #4]
_L00cc:
    mov     r0, r4
    add     sp, sp, #0xc
    ldmfd   sp!, {r4, r5, pc}
    dcd     func_ov066_020b66d0
}
