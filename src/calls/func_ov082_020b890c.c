extern void func_ov082_020b8970(void);
extern void func_ov082_020b8984(void);
extern void func_ov082_020b9ff0(void);

asm void func_ov082_020b890c(void)
{
    dcd     0xe92d4008
    dcd     0xe28020a8
    dcd     0xe3510022
    dcd     0xe3a00000
    dcd     0x0a000002
    dcd     0xe3510023
    dcd     0x0a000005
    dcd     0xe8bd8008
    dcd     0xe2820b0b
    dcd     0xe3a01022
    bl      func_ov082_020b9ff0
    dcd     0xe59f0014
    dcd     0xe8bd8008
    dcd     0xe2820b0b
    dcd     0xe3a01023
    bl      func_ov082_020b9ff0
    dcd     0xe59f0004
    dcd     0xe8bd8008
    dcd     func_ov082_020b8970
    dcd     func_ov082_020b8984
}
