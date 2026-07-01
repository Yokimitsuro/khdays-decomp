extern void func_ov022_0209fb60(void);
extern void func_ov022_0209fb98(void);
extern char data_ov102_020bb920[];

asm void func_ov102_020baa14(void)
{
    push    {r4, lr}
    ldr     r0, =data_ov102_020bb920
    mov     r1, #1
    ldr     r4, [r0, #0]
    mov     r2, #2
    mov     r0, r4
    bl      func_ov022_0209fb60
    mov     r1, #1
    mov     r0, r4
    mov     r2, r1
    bl      func_ov022_0209fb98
    ldr     r1, =0xf0d
    ldrsb   r0, [r4, r1]
    cmp     r0, #0
    beq     _done
    sub     r0, r1, #1
    ldrb    r2, [r4, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r4, r0]
_done:
    pop     {r4, pc}
}
