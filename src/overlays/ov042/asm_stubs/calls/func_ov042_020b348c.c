extern void func_ov022_0209fb60(void);
extern void func_ov022_0209fb98(void);

asm void func_ov042_020b348c(void)
{
    push    {r4, lr}
    mov     r4, r0
    mov     r1, #0
    mov     r2, #1
    bl      func_ov022_0209fb60
    mov     r0, r4
    mov     r1, #0
    mov     r2, #1
    bl      func_ov022_0209fb98
    ldr     r1, =0xda9
    ldrsb   r0, [r4, r1]
    cmp     r0, #0
    beq     _020b348c_done
    sub     r0, r1, #1
    ldrb    r2, [r4, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r4, r0]
_020b348c_done:
    pop     {r4, pc}
}
