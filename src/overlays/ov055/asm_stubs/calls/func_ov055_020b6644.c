extern void func_02030788(void);
extern void func_02033d0c(void);
extern void data_ov055_020b7740(void);

asm void func_ov055_020b6644(void)
{
    dcd     0xe92d41f0
    dcd     0xe59f20ac
    dcd     0xe1a08000
    dcd     0xe5924000
    dcd     0xe5985008
    dcd     0xe1a07001
    dcd     0xe3a00004
    dcd     0xe5c70002
    dcd     0xe3a00a03
    dcd     0xe5870004
    dcd     0xe3a06000
    bl      func_02030788
    dcd     0xe5d41008
    dcd     0xe1510000
    dcd     0x1a000004
    dcd     0xe5940000
    dcd     0xe3100801
    dcd     0x03860001
    dcd     0x01a00800
    dcd     0x01a06820
    dcd     0xe5980000
    dcd     0xe3500001
    dcd     0x1a000009
    dcd     0xe5d50694
    dcd     0xe1a00f80
    dcd     0xe1b00fa0
    dcd     0x0a000010
    dcd     0xe1a03006
    dcd     0xe28720cc
    dcd     0xe3a000cc
    dcd     0xe3a01000
    bl      func_02033d0c
    dcd     0xea00000a
    dcd     0xe3500002
    dcd     0x1a000008
    dcd     0xe5d50694
    dcd     0xe1a00f80
    dcd     0xe1b00fa0
    dcd     0x0a000004
    dcd     0xe1a03006
    dcd     0xe28720cc
    dcd     0xe3a000cc
    dcd     0xe3a01001
    bl      func_02033d0c
    mov r0, #0
    dcd     0xe8bd81f0
    dcd     data_ov055_020b7740
}
