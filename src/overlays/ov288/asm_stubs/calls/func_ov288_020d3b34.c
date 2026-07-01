extern void func_ov107_020c7a90(void);

asm void func_ov288_020d3b34(void *r0, void *r1)
{
    ldrb    r3, [r1, #2]
    ldr     ip, =func_ov107_020c7a90
    cmp     r3, #0
    ldreq   r3, [r0, #0x394]
    streqb  r3, [r1, #0x24]
    bx      ip
}
