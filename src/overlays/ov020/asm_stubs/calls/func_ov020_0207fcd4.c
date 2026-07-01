extern void *func_ov002_02076a38(int r0, int r1);
extern void func_02023c60(int r0);
extern void func_ov002_02076480(int r0);
extern int func_ov020_0207fbdc(void);

asm void *func_ov020_0207fcd4(int r0, int r1, int r2, int r3, int s0)
{
    push    {r3, r4, r5, r6, lr}
    sub     sp, #0xc
    add     r5, r2, #0
    add     r6, r3, #0
    bl      func_ov002_02076a38
    add     r4, r0, #0
    mov     r0, #0
    add     r2, r4, #0
    add     r3, sp, #0
    str     r0, [sp]
    str     r0, [sp, #4]
    str     r0, [sp, #8]
    ldmia   r3!, {r0, r1}
    add     r2, #0xc0
    stmia   r2!, {r0, r1}
    ldr     r0, [r3, #0]
    str     r0, [r2, #0]
    mov     r0, #0x49
    lsl     r0, r0, #2
    add     r0, r4, r0
    bl      func_02023c60
    ldr     r0, =func_ov020_0207fbdc
    strb    r5, [r4, #0x10]
    str     r0, [r4, #0xc]
    strh    r6, [r4, #0x14]
    add     r0, sp, #0x10
    ldrb    r0, [r0, #0x10]
    add     r1, r4, #0
    strb    r0, [r4, #0x16]
    mov     r0, #0
    strb    r0, [r4, #0x17]
    add     r0, r5, #0
    bl      func_ov002_02076480
    add     r0, r4, #0
    add     sp, #0xc
    pop     {r3, r4, r5, r6, pc}
}
