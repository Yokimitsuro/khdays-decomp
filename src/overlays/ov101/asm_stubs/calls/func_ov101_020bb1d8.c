extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void VEC_Add(void);
extern char data_0203d210[];
extern char data_ov101_020bc0e0[];
extern void func_02030788(void);
extern void func_02033d0c(void);
extern void func_ov101_020bb95c(void);

asm void func_ov101_020bb1d8(void)
{
    dcd     0xe92d4ff8
    dcd     0xe24dd048
    dcd     0xe59f0144
    dcd     0xe1a0b001
    dcd     0xe590a000
    dcd     0xe3a00004
    dcd     0xe5cb0002
    dcd     0xe3a00a03
    dcd     0xe58b0004
    dcd     0xe1db02fa
    dcd     0xe3a08000
    dcd     0xe3500002
    dcd     0x1a000030
    dcd     0xe28b00cc
    dcd     0xe28d303c
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe59a0020
    dcd     0xe59f6108
    dcd     0xe1d008b0
    dcd     0xe28d7000
    dcd     0xe28d5030
    dcd     0xe2400902
    dcd     0xe1a00800
    dcd     0xe1a09820
    dcd     0xe28d4024
    dcd     0xe1a00249
    dcd     0xe1a00080
    dcd     0xe1a01080
    dcd     0xe0860080
    dcd     0xe1d020f2
    dcd     0xe3a03000
    dcd     0xe19610f1
    dcd     0xe1a00007
    dcd     0xe2622000
    dcd     0xe2611000
    dcd     0xe58d3030
    dcd     0xe58d3034
    dcd     0xe3a03a03
    dcd     0xe58d3038
    bl      MTX_RotY33_
    dcd     0xe1a00005
    dcd     0xe1a01007
    dcd     0xe1a02005
    bl      MTX_MultVec33
    dcd     0xe1a00005
    dcd     0xe28d103c
    dcd     0xe1a02004
    bl      VEC_Add
    dcd     0xe28a0db2
    dcd     0xe1a01004
    bl      func_ov101_020bb95c
    dcd     0xe2890055
    dcd     0xe2800c55
    dcd     0xe1a00800
    dcd     0xe2888001
    dcd     0xe1a09820
    dcd     0xe3580003
    dcd     0xbaffffde
    bl      func_02030788
    dcd     0xe3a08001
    dcd     0xea00000a
    dcd     0xe3500001
    dcd     0x1a000008
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000005
    dcd     0xe59a1000
    dcd     0xe1a00008
    dcd     0xe3110801
    dcd     0x03a01003
    dcd     0x05ca147a
    dcd     0x05ca047b
    dcd     0xe5da0694
    dcd     0xe1a00f80
    dcd     0xe1b00fa0
    dcd     0x0a000004
    dcd     0xe1a01008
    dcd     0xe28b20cc
    dcd     0xe3a000d6
    dcd     0xe3a03000
    bl      func_02033d0c
    mov r0, #0
    dcd     0xe28dd048
    dcd     0xe8bd8ff8
    dcd     data_ov101_020bc0e0
    dcd     data_0203d210
}
