extern void func_ov107_020c5c54(void);
extern void func_02023eb4(void);
extern void func_01fffd70(void);
extern void func_01fffd8c(void);
extern void func_ov107_020cab14(void);
extern void FX_Sqrt(void);
extern void func_0203c634(void);

asm void func_ov288_020d5218(void)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, lr}
    mov     r5, r0
    ldmia   r5, {r0, r4}
    ldr     r1, [r4, #0x34]
    ldr     r0, [r0, #0x2c]
    add     r0, r1, r0
    str     r0, [r4, #0x34]
    cmp     r0, #0x1000
    ldmltfd sp!, {r3, r4, r5, r6, r7, pc}
    mov     r0, #0x1000
    str     r0, [r4, #0x34]
    ldr     r0, [r4]
    add     r1, r0, #0x190
    bl      func_ov107_020c5c54
    ldr     r0, [r4]
    ldr     r0, [r0, #0x3b8]
    cmp     r0, #0
    ble     _L_0094
    bl      func_02023eb4
    ldr     r1, [r4]
    mov     r6, r0
    add     r0, r1, #0x398
    bl      func_01fffd70
    movs    r1, r0
    mov     r7, #0
    beq     _L_0094
_L_0068:
    cmp     r7, r6
    blt     _L_007c
    ldr     r0, [r4]
    bl      func_ov107_020c5c54
    b       _L_0094
_L_007c:
    ldr     r0, [r4]
    add     r0, r0, #0x398
    bl      func_01fffd8c
    movs    r1, r0
    add     r7, r7, #1
    bne     _L_0068
_L_0094:
    ldr     r0, [r4]
    add     r1, sp, #0
    bl      func_ov107_020cab14
    cmp     r0, #0
    beq     _L_00b8
    ldr     r0, [sp]
    bl      FX_Sqrt
    cmp     r0, #0x800
    ldmlefd sp!, {r3, r4, r5, r6, r7, pc}
_L_00b8:
    ldr     lr, [r4]
    mov     r3, #1
    ldrh    ip, [lr, #0x60]
    mov     r0, r5
    mov     r2, #0
    mov     r1, ip, lsl #0x10
    mov     r1, r1, lsr #0x18
    orr     r1, r1, #1
    bic     ip, ip, #0xff00
    mov     r1, r1, lsl #0x18
    orr     r1, ip, r1, lsr #16
    strh    r1, [lr, #0x60]
    ldr     r1, [r4]
    strb    r3, [r1, #0x1c7]
    ldrsb   r1, [r5, #0x20]
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
}
