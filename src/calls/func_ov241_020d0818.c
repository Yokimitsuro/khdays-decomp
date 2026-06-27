extern void func_0203c634(void);

asm void func_ov241_020d0818(void *r0)
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
