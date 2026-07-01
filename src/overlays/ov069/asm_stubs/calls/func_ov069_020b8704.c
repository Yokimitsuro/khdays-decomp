extern void func_020235d0(void);
extern void func_02023588(void);
extern void data_ov069_020ba7f8(void);
extern void data_ov069_020ba7fa(void);

asm void func_ov069_020b8704(void)
{
    dcd     0xe92d4008
    mov r0, #0
    dcd     0xe3a01009
    bl      func_020235d0
    dcd     0xe1a00800
    dcd     0xe3a0c000
    dcd     0xe59f1040
    dcd     0xe1a0e00c
    dcd     0xe1a03820
    dcd     0xe1a0218e
    dcd     0xe19100b2
    dcd     0xe1530000
    dcd     0x359f002c
    dcd     0x3190c0b2
    dcd     0x3a000004
    dcd     0xe28e0001
    dcd     0xe1a00800
    dcd     0xe1a0e820
    dcd     0xe35e0038
    dcd     0x3afffff4
    dcd     0xe28c00d5
    dcd     0xe2800c3b
    bl      func_02023588
    dcd     0xe8bd8008
    dcd     data_ov069_020ba7f8
    dcd     data_ov069_020ba7fa
}
