extern char data_02041dc8[];
extern char data_ov032_020b5700[];
extern void func_ov022_020893f4(void);
extern void func_ov022_020894cc(void);
extern void func_ov022_0208954c(void);
extern void func_ov022_020a4490(void);

asm void func_ov032_020b4034(void)
{
    dcd     0xe92d4ff8
    dcd     0xe24dd010
    dcd     0xe59f10f0
    dcd     0xe28db000
    dcd     0xe1a09000
    dcd     0xe891000f
    dcd     0xe2894f4a
    dcd     0xe3a07000
    dcd     0xe2848b01
    dcd     0xe88b000f
    dcd     0xe2894a02
    dcd     0xe289ac07
    dcd     0xe1a05007
    dcd     0xe08b0187
    dcd     0xe5993464
    dcd     0xe79b1187
    dcd     0xe5992468
    dcd     0xe5900004
    dcd     0xe0031001
    dcd     0xe0022000
    mov r0, #0
    dcd     0xe1520000
    dcd     0x01510005
    dcd     0x0a000021
    dcd     0xe5940c2c
    dcd     0xe59f1098
    dcd     0xe3a02000
    bl      func_ov022_020893f4
    dcd     0xe1b06000
    dcd     0x428dd010
    dcd     0x48bd8ff8
    dcd     0xe5940c2c
    dcd     0xe1a01006
    dcd     0xe1a02008
    bl      func_ov022_0208954c
    dcd     0xe5940c2c
    dcd     0xe1a01006
    dcd     0xe3a02000
    bl      func_ov022_020894cc
    dcd     0xe59906bc
    dcd     0xe2400025
    dcd     0xe3500005
    dcd     0x908ff100
    dcd     0xea000009
    dcd     0xea000006
    dcd     0xea000003
    dcd     0xea000004
    dcd     0xea000001
    dcd     0xea000000
    dcd     0xea000001
    dcd     0xe3a02005
    dcd     0xea000002
    dcd     0xe3a02007
    dcd     0xea000000
    dcd     0xe3a02002
    dcd     0xe1a00009
    dcd     0xe1da1af6
    bl      func_ov022_020a4490
    dcd     0xe2888030
    dcd     0xe2877001
    dcd     0xe3570002
    dcd     0xbaffffce
    dcd     0xe28dd010
    dcd     0xe8bd8ff8
    dcd     data_ov032_020b5700
    dcd     data_02041dc8
}
