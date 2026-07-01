extern char data_ov046_020b4aa0[];
extern void func_02023930(void);

asm void func_ov046_020b4a40(void)
{
    ldr ip, [pc, #8]
    dcd     0xe1a01000
    dcd     0xe59f0004
    bx  ip
    dcd     func_02023930
    dcd     data_ov046_020b4aa0
}
