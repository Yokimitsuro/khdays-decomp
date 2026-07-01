#pragma thumb on

extern void func_02023588(void);
extern void func_ov002_02051d6c(void);
extern void func_ov002_02051eec(void);
extern void func_ov022_0209fb60(void);
extern int data_0204c240;
extern int data_0204c678;
extern int data_ov030_020b5a00;

asm void func_ov030_020b35dc(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    add     r5, r0, #0
    ldr     r0, [pc, #0x90]
    mov     r6, #1
    ldr     r4, [r0, #0]
    ldr     r0, [pc, #0x90]
    ldrb    r1, [r0]
    mov     r0, #4
    tst     r0, r1
    beq     _L_0018
    add     r7, r6, #0
    b       _L_0046
_L_0018:
    ldrb    r2, [r5, #9]
    ldr     r0, [pc, #0x84]
    lsl     r1, r2, #6
    add     r1, r2, r1
    lsl     r1, r1, #2
    add     r7, r0, r1
    ldr     r0, [pc, #0x7c]
    bl      func_02023588
    cmp     r0, #0
    bne     _L_0034
    ldrb    r0, [r7, #4]
    cmp     r0, #0x30
    bne     _L_0038
_L_0034:
    mov     r7, #1
    b       _L_003a
_L_0038:
    mov     r7, #0
_L_003a:
    ldr     r0, [pc, #0x6c]
    bl      func_02023588
    cmp     r0, #0
    beq     _L_0046
    mov     r6, #0
_L_0046:
    cmp     r6, #0
    beq     _L_0094
    add     r0, r4, #0
    mov     r1, #1
    mov     r2, #2
    bl      func_ov022_0209fb60
    cmp     r7, #0
    beq     _L_006c
    ldr     r1, [pc, #0x50]
    ldrsb   r0, [r4, r1]
    cmp     r0, #0
    beq     _L_006c
    sub     r0, r1, #1
    ldrb    r2, [r4, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r4, r0]
_L_006c:
    ldr     r0, [pc, #0x40]
    ldr     r1, [pc, #0x44]
    mov     r2, #0x91
    lsl     r2, r2, #4
    add     r0, r4, r0
    add     r1, r4, r1
    add     r2, r5, r2
    bl      func_ov002_02051d6c
    mov     r0, #0x78
    str     r0, [sp]
    ldr     r2, [pc, #0x30]
    ldr     r0, [pc, #0x28]
    add     r1, r4, r2
    sub     r2, #0x84
    ldrb    r3, [r5, #9]
    ldr     r2, [r5, r2]
    add     r0, r5, r0
    bl      func_ov002_02051eec
_L_0094:
    pop     {r3, r4, r5, r6, r7, pc}
    mov     r8, r8
    dcd     data_ov030_020b5a00
    dcd     data_0204c240
    dcd     data_0204c678
    dcd     0x00002089
    dcd     0x0000208b
    dcd     0x00000f0d
    dcd     0x00000f0c
    dcd     0x00002c54
}
