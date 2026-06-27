#pragma thumb on

extern void func_0202a634(void);
extern void func_ov022_02092384(void);
extern void func_ov030_020b3e9c(void);
extern int data_ov030_020b58c4;
extern int data_ov030_020b59ac;
extern int data_ov030_020b59c0;
extern int data_ov030_020b59d4;

asm void func_ov030_020b4b9c(void)
{
    push    {r3, r4, r5, r6, lr}
    sub     sp, #0x14
    add     r5, r0, #0
    add     r4, r1, #0
    ldr     r0, [pc, #0x74]
    mov     r1, #0
    str     r5, [r4, r0]
    str     r1, [r4, #0xc]
    mov     r0, #0x23
    str     r1, [r4, #0x14]
    lsl     r0, r0, #4
    str     r1, [r4, r0]
    ldrb    r3, [r5, #9]
    add     r0, r4, #0
    ldr     r1, [pc, #0x64]
    add     r0, #0x18
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202a634
    ldr     r0, [r5, #0xc]
    cmp     r0, #0
    bne     _L_0042
    ldrb    r3, [r5, #9]
    mov     r0, #0x4a
    lsl     r0, r0, #2
    ldr     r1, [pc, #0x50]
    add     r0, r4, r0
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202a634
    b       _L_0054
_L_0042:
    ldrb    r3, [r5, #9]
    mov     r0, #0x4a
    lsl     r0, r0, #2
    ldr     r1, [pc, #0x40]
    add     r0, r4, r0
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202a634
_L_0054:
    ldr     r6, [pc, #0x38]
    add     r2, sp, #0
    ldmia   r6!, {r0, r1}
    add     r3, r2, #0
    stmia   r2!, {r0, r1}
    ldmia   r6!, {r0, r1}
    stmia   r2!, {r0, r1}
    ldr     r0, [r6, #0]
    str     r0, [r2, #0]
    mov     r0, #4
    str     r0, [sp, #4]
    ldr     r0, [pc, #0x28]
    ldrb    r1, [r5, #9]
    add     r0, r5, r0
    mov     r2, #5
    bl      func_ov022_02092384
    add     r0, r4, #0
    bl      func_ov030_020b3e9c
    add     sp, #0x14
    pop     {r3, r4, r5, r6, pc}
    dcd     0x00000db4
    dcd     data_ov030_020b59ac
    dcd     data_ov030_020b59c0
    dcd     data_ov030_020b59d4
    dcd     data_ov030_020b58c4
    dcd     0x00002648
}
