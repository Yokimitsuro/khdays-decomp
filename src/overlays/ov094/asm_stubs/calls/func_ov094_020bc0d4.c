extern void func_02023930(void);
extern void data_ov094_020bc174(void);

asm void func_ov094_020bc0d4(void)
{
    ldr ip, [pc, #8]
    dcd     0xe1a01000
    dcd     0xe59f0004
    bx  ip
    dcd     func_02023930
    dcd     data_ov094_020bc174
}
