extern char data_ov090_020bcc00[];
extern void func_0202a7dc(void);

asm void func_ov090_020bc6ac(void)
{
    ldr     r0, [pc, #8]
    ldr     r3, [pc, #0xc]
    ldr     r1, [r0, #0]
    ldr     r0, [pc, #0xc]
    add     r0, r1, r0
    bx      r3
    dcd     data_ov090_020bcc00
    dcd     func_0202a7dc
    cmp     r5, #0xc
    lsl     r0, r0, #0
}
