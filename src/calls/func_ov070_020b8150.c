extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_0202b850(void);
extern void func_0202b914(void);
extern void func_0202bfcc(void);
extern void func_0202d968(void);
extern void func_02016f10(void);
extern void func_ov022_0209f6e0(void);
extern void *data_ov070_020b9ca0;
extern void *data_ov070_020b9bdc;
extern void *data_ov070_020b9bf0;
extern void func_ov070_020b8414(void);
extern void func_ov070_020b84f0(void);
extern void func_ov070_020b8608(void);
extern void func_ov070_020b8390(void);
extern void func_ov070_020b83ec(void);
extern void func_ov070_020b8638(void);
extern void func_ov070_020b8710(void);
extern void func_ov070_020b9000(void);
extern void *data_ov070_020b9b70;
extern void *data_ov070_020b9b80;
extern void *data_ov070_020b9b50;
extern void *data_ov070_020b9b40;
extern void *data_ov070_020b9b60;

asm void func_ov070_020b8150(void)
{
    push    {r3, r4, r5, lr}
    sub     sp, #0x18
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, =data_ov070_020b9ca0
    mov     r3, #9
    str     r4, [r0, #0]
    ldr     r0, [r5, #0]
    mov     r2, #0
    strb    r0, [r4, #9]
    ldr     r1, [r5, #4]
    ldr     r0, =0x4bc
    lsl     r3, r3, #8
    strb    r1, [r4, r0]
    ldrb    r1, [r5, #8]
    strb    r1, [r4, #8]
    mov     r1, #1
    str     r1, [r4, #0xc]
    str     r2, [r4, #0]
    str     r2, [r4, #4]
    str     r3, [sp, #0xc]
    mov     r3, #0x17
    lsl     r3, r3, #8
    str     r1, [sp, #4]
    str     r3, [sp, #8]
    str     r2, [sp, #0]
    ldrb    r3, [r4, #8]
    ldrsb   r0, [r4, r0]
    lsl     r1, r3
    lsl     r1, r1, #0x10
    lsr     r1, r1, #0x10
    add     r3, sp, #4
    bl      func_0202b850
    ldr     r0, [r5, #0x18]
    cmp     r0, #0
    ldr     r0, =0x4bc
    bne     _L_60
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, =data_ov070_020b9bdc
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202b914
    b       _L_6e
_L_60:
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, =data_ov070_020b9bf0
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202b914
_L_6e:
    ldr     r1, =func_ov070_020b8414
    ldr     r0, =0x664
    ldr     r2, =func_ov070_020b84f0
    str     r1, [r4, r0]
    add     r1, r0, #4
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, =func_ov070_020b8608
    add     r1, #8
    str     r2, [r4, r1]
    add     r2, r0, #0
    mov     r1, #0
    add     r2, #0xc
    str     r1, [r4, r2]
    add     r2, r0, #0
    add     r2, #0x10
    str     r1, [r4, r2]
    add     r2, r0, #0
    ldr     r3, =func_ov070_020b8390
    add     r2, #0x14
    str     r3, [r4, r2]
    add     r2, r0, #0
    ldr     r3, =func_ov070_020b83ec
    add     r2, #0x18
    str     r3, [r4, r2]
    add     r2, r0, #0
    ldr     r3, =func_ov070_020b8638
    add     r2, #0x20
    str     r3, [r4, r2]
    add     r2, r0, #0
    add     r2, #0x28
    str     r1, [r4, r2]
    add     r1, r0, #0
    ldr     r2, =func_ov070_020b8710
    add     r1, #0x28
    str     r2, [r4, r1]
    ldr     r1, =func_ov070_020b9000
    add     r0, #0x24
    str     r1, [r4, r0]
    ldr     r0, =0x4bc
    ldrsb   r0, [r4, r0]
    bl      func_0202bfcc
    add     r1, r0, #0
    add     r0, r4, #0
    add     r0, #0x20
    bl      func_0202d968
    mov     r3, #0
    sub     r2, r3, #1
    ldr     r0, =0x514
    b       _L_de
_L_d6:
    lsl     r1, r3, #2
    add     r1, r4, r1
    str     r2, [r1, r0]
    add     r3, r3, #1
_L_de:
    cmp     r3, #5
    blt     _L_d6
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_f0
    add     r0, #0x40
    b       _L_f2
_L_f0:
    mov     r0, #0
_L_f2:
    cmp     r0, #0
    beq     _L_fe
    ldr     r1, =data_ov070_020b9b70
    bl      func_02016f10
    b       _L_102
_L_fe:
    mov     r0, #0
    mvn     r0, r0
_L_102:
    mov     r1, #0x52
    lsl     r1, r1, #4
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_116
    add     r0, #0x40
    b       _L_118
_L_116:
    mov     r0, #0
_L_118:
    cmp     r0, #0
    beq     _L_124
    ldr     r1, =data_ov070_020b9b80
    bl      func_02016f10
    b       _L_128
_L_124:
    mov     r0, #0
    mvn     r0, r0
_L_128:
    ldr     r1, =0x518
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_13a
    add     r0, #0x40
    b       _L_13c
_L_13a:
    mov     r0, #0
_L_13c:
    cmp     r0, #0
    beq     _L_148
    ldr     r1, =data_ov070_020b9b50
    bl      func_02016f10
    b       _L_14c
_L_148:
    mov     r0, #0
    mvn     r0, r0
_L_14c:
    ldr     r1, =0x514
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_15e
    add     r0, #0x40
    b       _L_160
_L_15e:
    mov     r0, #0
_L_160:
    cmp     r0, #0
    beq     _L_16c
    ldr     r1, =data_ov070_020b9b40
    bl      func_02016f10
    b       _L_170
_L_16c:
    mov     r0, #0
    mvn     r0, r0
_L_170:
    ldr     r1, =0x51c
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_182
    add     r0, #0x40
    b       _L_184
_L_182:
    mov     r0, #0
_L_184:
    cmp     r0, #0
    beq     _L_190
    ldr     r1, =data_ov070_020b9b60
    bl      func_02016f10
    b       _L_194
_L_190:
    mov     r0, #0
    mvn     r0, r0
_L_194:
    ldr     r1, =0x524
    str     r0, [r4, r1]
    ldr     r0, [r5, #0xc]
    cmp     r0, #0
    beq     _L_1ae
    ldr     r3, [r4, #0]
    mov     r0, #0x20
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_1ae:
    ldr     r0, [r5, #0x10]
    cmp     r0, #0
    beq     _L_1c6
    mov     r0, #1
    ldr     r3, [r4, #0]
    lsl     r0, r0, #0x10
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_1c6:
    ldr     r0, [r5, #0x14]
    cmp     r0, #0
    beq     _L_1dc
    ldr     r3, [r4, #0]
    mov     r0, #0
    ldr     r2, [r4, #4]
    mov     r1, #0x10
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_1dc:
    add     r0, r4, #0
    bl      func_ov022_0209f6e0
    add     sp, #0x18
    pop     {r3, r4, r5, pc}
}
