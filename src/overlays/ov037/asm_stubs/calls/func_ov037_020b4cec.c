extern char data_ov037_020b4d94[];
extern void func_02023930(void);

asm void func_ov037_020b4cec(void)
{
    ldr ip, [pc, #8]
    dcd     0xe1a01000
    dcd     0xe59f0004
    bx  ip
    dcd     func_02023930
    dcd     data_ov037_020b4d94
}
