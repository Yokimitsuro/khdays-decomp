extern void func_0202a634(void *a, void *b, int c, int d);
extern void *data_ov030_020b5998;

asm void func_ov030_020b3e9c(void *r0)
{
    push    {r3, r4, r5, r6, r7, lr}
    ldr     r1, =0xdb4
    mov     r4, #0
    ldr     r6, [r0, r1]
    mov     r1, #0x8d
    lsl     r1, r1, #0x2
    add     r5, r0, r1
    mov     r7, r4
_L_10:
    ldrb    r3, [r6, #0x9]
    ldr     r1, =data_ov030_020b5998
    mov     r0, r5
    mov     r2, #0x1
    add     r3, r3, #0x7
    bl      func_0202a634
    ldr     r0, =0x12d
    strb    r4, [r5, r0]
    sub     r0, r0, #0x1
    strb    r7, [r5, r0]
    mov     r0, #0x17
    lsl     r0, r0, #0x4
    add     r4, r4, #0x1
    add     r5, r5, r0
    cmp     r4, #0x8
    blt     _L_10
    pop     {r3, r4, r5, r6, r7, pc}
}
