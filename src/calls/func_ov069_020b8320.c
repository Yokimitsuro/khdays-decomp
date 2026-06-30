extern void func_ov002_0206e0f0(void);
extern void func_ov002_0206e144(void);
extern void func_02023588(void);
extern void func_ov002_0206e700(void);
extern void func_ov002_0206e184(void);

asm void func_ov069_020b8320(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    mov     r6, #0
    add     r4, r0, #0
    add     r0, r6, #0
    bl      func_ov002_0206e0f0
    add     r0, r4, #0
    bl      func_ov002_0206e144
    add     r7, r0, #0
    beq     _L_003e
    mov     r0, #2
    ldrsb   r0, [r7, r0]
    add     r4, r6, #0
    cmp     r0, #0
    ble     _L_003e
    add     r5, r7, #0
_L_0022:
    mov     r0, #8
    ldrsh   r0, [r5, r0]
    add     r0, #9
    bl      func_02023588
    cmp     r0, #0
    bne     _L_0032
    add     r6, r6, #1
_L_0032:
    mov     r0, #2
    ldrsb   r0, [r7, r0]
    add     r4, r4, #1
    add     r5, #0x14
    cmp     r4, r0
    blt     _L_0022
_L_003e:
    mov     r0, #1
    add     r1, r6, #0
    bl      func_ov002_0206e700
    bl      func_ov002_0206e184
    cmp     r6, #0
    bne     _L_0052
    mov     r0, #1
    pop     {r3, r4, r5, r6, r7, pc}
_L_0052:
    mov     r0, #0
    pop     {r3, r4, r5, r6, r7, pc}
}
