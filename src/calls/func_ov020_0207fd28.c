extern void func_ov002_02072aa0(int a, int b, int c, int d);
extern void MIi_CpuClearFast(int a, int b, int c);
extern int func_ov002_02072754(int a);
extern void func_ov002_020726f4(int a, int b, int c);
extern int func_0202af1c(void *a);
extern int *func_0202bfa0(int a);
extern int func_02028df0(int a);
extern void func_02028e4c(int a, int b, int c, int d, int e);
extern void *func_0202c3c4(int a);
extern int data_ov020_020800d8;
extern int data_ov020_020800e4;
extern int data_ov020_020800f0;
extern int data_ov020_020800fc;
extern int data_ov020_02080100;
extern void func_ov002_02072b24(void);

asm void func_ov020_0207fd28(void *a, void *b, void *c)
{
    push    {r3, r4, r5, r6, r7, lr}
    sub     sp, #0x10
    add     r4, r1, #0
    str     r0, [sp, #4]
    str     r2, [sp, #8]
    ldr     r0, =data_ov020_020800d8
    mov     r1, #8
    mov     r2, #1
    add     r3, r4, #0
    bl      func_ov002_02072aa0
    ldr     r1, [sp, #4]
    mov     r0, #0
    mov     r2, #0x20
    bl      MIi_CpuClearFast
    add     r0, r4, #0
    bl      func_ov002_02072754
    cmp     r0, #9
    bne     _L2e
    mov     r2, #1
    b       _L30
_L2e:
    mov     r2, #0
_L30:
    ldr     r1, [sp, #4]
    cmp     r2, #0
    str     r2, [r1, #0x10]
    beq     _L3c
    mov     r1, #7
    b       _L3e
_L3c:
    mov     r1, #0x46
_L3e:
    mov     r2, #1
    bl      func_ov002_020726f4
    mov     r1, #0x11
    ldr     r0, [sp, #8]
    lsl     r1, r1, #4
    ldrsb   r0, [r0, r1]
    mov     r4, #0
    cmp     r0, #0
    ble     _L80
    mov     r7, #0x43
    lsl     r7, r7, #2
    ldr     r0, [sp, #8]
    add     r1, r1, #4
    add     r5, r0, r1
    add     r6, r7, #4
_L5e:
    mov     r0, #0x42
    lsl     r0, r0, #2
    ldrb    r1, [r5, r0]
    mov     r0, #2
    orr     r1, r0
    mov     r0, #0x42
    lsl     r0, r0, #2
    strb    r1, [r5, r0]
    add     r0, r5, #0
    bl      func_0202af1c
    ldr     r0, [sp, #8]
    add     r4, r4, #1
    ldrsb   r0, [r0, r6]
    add     r5, r5, r7
    cmp     r4, r0
    blt     _L5e
_L80:
    ldr     r0, [sp, #8]
    mov     r1, #0xd
    ldrsb   r0, [r0, r1]
    bl      func_0202bfa0
    add     r4, r0, #0
    ldr     r0, [sp, #4]
    ldr     r0, [r0, #0x10]
    cmp     r0, #0
    beq     _L9a
    ldr     r0, =data_ov020_020800e4
    str     r0, [sp, #0xc]
    b       _L9e
_L9a:
    ldr     r0, =data_ov020_020800f0
    str     r0, [sp, #0xc]
_L9e:
    ldrh    r0, [r4, #2]
    mov     r6, #0
    cmp     r0, #0
    ble     _Lce
    add     r5, r6, #0
_La8:
    ldr     r0, [r4, #4]
    ldr     r1, [sp, #0xc]
    ldr     r7, [r0, r5]
    add     r0, r7, #0
    bl      func_02028df0
    add     r2, r0, #0
    mov     r0, #0
    str     r0, [sp]
    ldr     r3, =func_ov002_02072b24
    add     r0, r7, #0
    mov     r1, #2
    bl      func_02028e4c
    ldrh    r0, [r4, #2]
    add     r6, r6, #1
    add     r5, r5, #4
    cmp     r6, r0
    blt     _La8
_Lce:
    ldr     r0, [sp, #4]
    ldr     r0, [r0, #0x10]
    cmp     r0, #0
    beq     _Lda
    ldr     r1, =data_ov020_020800fc
    b       _Ldc
_Lda:
    ldr     r1, =data_ov020_02080100
_Ldc:
    ldr     r0, [sp, #8]
    mov     r2, #0xd
    ldrsb   r0, [r0, r2]
    bl      func_0202c3c4
    add     r3, r0, #0
    add     r3, #8
    ldr     r2, [sp, #4]
    ldmia   r3!, {r0, r1}
    stmia   r2!, {r0, r1}
    ldr     r0, [r3, #0]
    mov     r1, #0
    str     r0, [r2]
    ldr     r0, [sp, #4]
    str     r1, [r0, #4]
    ldr     r1, =0x4ccd
    str     r1, [r0, #0xc]
    mov     r1, #1
    str     r1, [r0, #0x14]
    add     sp, #0x10
    pop     {r3, r4, r5, r6, r7, pc}
}
