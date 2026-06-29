extern char data_ov032_020b5724[];
extern char data_ov032_020b587c[];
extern char data_ov032_020b58c0[];
extern void func_0202a634(void);
extern void func_ov022_02092384(void);
extern void func_ov032_020b4da4(void);

asm void func_ov032_020b4994(void)
{
    push    {r3, r4, r5, r6, lr}
    sub     sp, #0x14
    add     r5, r0, #0
    ldr     r0, [pc, #0x48]
    mov     r1, #0x45
    ldr     r4, [r0, #0]
    ldr     r0, [pc, #0x44]
    mov     r2, #0
    add     r0, r4, r0
    lsl     r1, r1, #2
    strb    r2, [r0, r1]
    str     r2, [r0, #0]
    str     r2, [r0, #4]
    ldrb    r3, [r4, #9]
    ldr     r1, [pc, #0x38]
    add     r0, #0xc
    mov     r2, #1
    add     r3, r3, #7
_L_0024:
    bl      func_0202a634
    ldr     r6, [pc, #0x30]
    add     r2, sp, #0
    ldmia   r6!, {r0, r1}
    add     r3, r2, #0
    stmia   r2!, {r0, r1}
    ldmia   r6!, {r0, r1}
    stmia   r2!, {r0, r1}
    ldr     r0, [r6, #0]
    str     r0, [r2, #0]
    ldr     r0, [pc, #0x24]
    ldrb    r1, [r5, #9]
    add     r0, r5, r0
    mov     r2, #5
_L_0042:
    bl      func_ov022_02092384
    add     r0, r4, #0
_L_0048:
    bl      func_ov032_020b4da4
    add     sp, #0x14
    pop     {r3, r4, r5, r6, pc}
    dcd     data_ov032_020b58c0
    cmp     r6, #0x78
    lsl     r0, r0, #0
    dcd     data_ov032_020b587c
    dcd     data_ov032_020b5724
    mov     r6, #0x48
    lsl     r0, r0, #0
}
