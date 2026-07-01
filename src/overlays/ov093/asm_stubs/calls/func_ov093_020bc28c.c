extern char data_ov093_020bc334[];
extern void func_02023930(void);

asm void func_ov093_020bc28c(void)
{
    ldr ip, [pc, #8]
    dcd     0xe1a01000
    dcd     0xe59f0004
    bx  ip
    dcd     func_02023930
    dcd     data_ov093_020bc334
}
