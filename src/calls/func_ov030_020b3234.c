#pragma thumb on

extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_0201ef9c(void);
extern void func_02023588(void);
extern void func_02023930(void);
extern void func_0202a3cc(void);
extern void func_ov022_0209fb24(void);
extern void func_ov022_020a4798(void);
extern void func_ov030_020b3374(void);
extern void func_ov030_020b4b9c(void);
extern int data_0204c240;
extern int data_ov022_020b2930;
extern int data_ov030_020b58b0;
extern int data_ov030_020b5908;

asm void func_ov030_020b3234(void)
{
    push    {r3, r4, r5, r6, lr}
    sub     sp, #0x14
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    ldr     r1, [pc, #0xa8]
    add     r4, r0, #0
    mov     r2, #0
    add     r0, r1, #0
    str     r2, [r4, r1]
    add     r0, #0x5c
    str     r2, [r4, r0]
    mov     r0, #2
    lsl     r0, r0, #0x1e
    add     r1, #0x58
    str     r0, [r4, r1]
    add     r0, r5, #0
    bl      func_ov030_020b3374
    ldr     r0, [pc, #0x90]
    ldrb    r1, [r0]
    mov     r0, #4
    tst     r0, r1
    bne     _L_009a
    ldr     r1, [r5, #0]
    ldr     r0, [pc, #0x88]
    add     r1, r1, #7
    bl      func_0201ef9c
    ldr     r2, [pc, #0x78]
    str     r0, [r4, r2]
    add     r0, r2, #0
    ldr     r1, [r4, #0x20]
    ldr     r3, [r5, #0]
    sub     r0, #0x24
    ldr     r2, [r4, r2]
    add     r0, r4, r0
    add     r1, r1, #4
    add     r3, r3, #7
    bl      func_0202a3cc
    mov     r0, #0
    ldr     r2, [pc, #0x68]
    mvn     r0, r0
    str     r0, [r4, r2]
    sub     r2, #0x58
    ldr     r2, [r4, r2]
    add     r0, r4, #0
    mov     r1, #0
    blx     r2
    ldr     r0, [pc, #0x5c]
    mov     r1, #0
    str     r1, [r4, r0]
    ldr     r0, [pc, #0x5c]
    bl      func_02023588
    cmp     r0, #0
    bne     _L_009a
    ldr     r6, [pc, #0x54]
    add     r3, sp, #0
    ldmia   r6!, {r0, r1}
    add     r2, r3, #0
    stmia   r3!, {r0, r1}
    ldmia   r6!, {r0, r1}
    stmia   r3!, {r0, r1}
    ldr     r0, [r6, #0]
    str     r0, [r3, #0]
    ldr     r1, [sp, #0x10]
    ldr     r0, [r5, #0]
    add     r0, r1, r0
    str     r0, [sp, #0x10]
    ldr     r0, [pc, #0x40]
    add     r1, r2, #0
    bl      func_02023930
    ldr     r1, [pc, #0x2c]
    str     r0, [r4, r1]
_L_009a:
    ldr     r1, [pc, #0x38]
    add     r0, r4, #0
    add     r1, r4, r1
    bl      func_ov030_020b4b9c
    add     r0, r4, #0
    mov     r1, #0x41
    mov     r2, #0xd0
    bl      func_ov022_020a4798
    ldr     r0, [pc, #0x28]
    add     sp, #0x14
    pop     {r3, r4, r5, r6, pc}
    dcd     0x00002c50
    dcd     data_0204c240
    dcd     data_ov030_020b5908
    dcd     0x000006bc
    dcd     0x00002cac
    dcd     0x00002089
    dcd     data_ov030_020b58b0
    dcd     data_ov022_020b2930
    dcd     0x00002cb0
    dcd     func_ov022_0209fb24
}
