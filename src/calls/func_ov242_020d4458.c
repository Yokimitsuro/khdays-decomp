extern int func_0203c634(void *r0, int r1, int r2);

asm void func_ov242_020d4458(void *r0)
{
    ldr     r1, [r0, #4]
    ldr     ip, =func_0203c634
    ldr     r1, [r1]
    mov     r3, #3
    strb    r3, [r1, #0x1c7]
    mov     r2, #0
    ldrsb   r1, [r0, #0x20]
    bx      ip
}
