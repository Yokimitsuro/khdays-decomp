extern char data_ov054_020b73f4[];
extern void func_02023930(void);

asm void func_ov054_020b7348(void)
{
    ldr ip, [pc, #8]
    dcd     0xe1a01000
    dcd     0xe59f0004
    bx  ip
    dcd     func_02023930
    dcd     data_ov054_020b73f4
}
