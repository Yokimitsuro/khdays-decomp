extern char data_ov032_020b58c0[];
extern void func_0202a7dc(void);

asm void func_ov032_020b49f8(void)
{
    ldr     r0, [pc, #8]
    ldr     r3, [pc, #0xc]
    ldr     r1, [r0, #0]
    ldr     r0, [pc, #0xc]
    add     r0, r1, r0
    bx      r3
    dcd     data_ov032_020b58c0
    dcd     func_0202a7dc
    cmp     r6, #0x84
    lsl     r0, r0, #0
}
