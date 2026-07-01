extern void func_02023930(void);
extern void data_ov055_020b7640(void);

asm void func_ov055_020b75f0(void)
{
    ldr ip, [pc, #8]
    dcd     0xe1a01000
    dcd     0xe59f0004
    bx  ip
    dcd     func_02023930
    dcd     data_ov055_020b7640
}
