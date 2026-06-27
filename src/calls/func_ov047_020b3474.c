extern void func_ov022_0209fb60(void *arg, int a, int b);
extern void func_ov022_0209fb98(void *arg, int a, int b);
extern int data_ov047_020b4380;

asm void func_ov047_020b3474(void)
{
    push    {r4, lr}
    ldr     r0, =data_ov047_020b4380
    mov     r1, #1
    ldr     r4, [r0, #0]
    mov     r2, #2
    add     r0, r4, #0
    bl      func_ov022_0209fb60
    mov     r1, #1
    add     r0, r4, #0
    add     r2, r1, #0
    bl      func_ov022_0209fb98
    ldr     r1, =0xf0d
    ldrsb   r0, [r4, r1]
    cmp     r0, #0
    beq     _end
    sub     r0, r1, #1
    ldrb    r2, [r4, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r4, r0]
_end:
    pop     {r4, pc}
}
