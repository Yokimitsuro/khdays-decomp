extern int func_0203c634();
extern void func_ov301_020cc748(void *p);

asm void func_ov301_020cc6fc(void *r0)
{
    ldr     r3, [r0, #4]
    ldr     ip, =func_0203c634
    ldr     r1, [r3]
    add     r1, r1, #0x100
    ldrh    r2, [r1, #0xae]
    orr     r2, r2, #3
    strh    r2, [r1, #0xae]
    ldr     r2, [r3]
    add     r1, r2, #0x200
    ldrsh   r3, [r1, #0x18]
    add     r1, r2, #0x200
    ldr     r2, =func_ov301_020cc748
    cmp     r3, #0
    movge   r3, #0
    strh    r3, [r1, #0x1a]
    ldrsb   r1, [r0, #0x20]
    bx      ip
}
