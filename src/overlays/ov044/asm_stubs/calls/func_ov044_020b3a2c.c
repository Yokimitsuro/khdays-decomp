extern void func_ov044_020b3a90(void);
extern void func_ov044_020b3aa4(void);
extern void func_ov044_020b5110(void);

asm void func_ov044_020b3a2c(void)
{
    dcd     0xe92d4008
    dcd     0xe28020a8
    dcd     0xe3510022
    mov r0, #0
    dcd     0x0a000002
    dcd     0xe3510023
    dcd     0x0a000005
    dcd     0xe8bd8008
    dcd     0xe2820b0b
    dcd     0xe3a01022
    bl      func_ov044_020b5110
    dcd     0xe59f0014
    dcd     0xe8bd8008
    dcd     0xe2820b0b
    dcd     0xe3a01023
    bl      func_ov044_020b5110
    dcd     0xe59f0004
    dcd     0xe8bd8008
    dcd     func_ov044_020b3a90
    dcd     func_ov044_020b3aa4
}
