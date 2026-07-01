extern void func_ov011_0205cad8(void);
extern void func_ov011_0205bb58(void);
extern void func_ov011_0205cff0(void);
extern void func_020325a0(void);
extern void func_0203257c(void);
extern void func_02032710(void);
extern void func_02032748(void);
extern void func_0203256c(void);
extern void data_ov011_0205e960(void);

asm void func_ov011_0205c3a0(void)
{
    dcd     0xe92d4ff0
    dcd     0xe24dd00c
    bl      func_ov011_0205cad8
    mov r0, #0
    dcd     0xe3a01001
    bl      func_ov011_0205bb58
    mov r0, #1
    dcd     0xe1a01000
    bl      func_ov011_0205bb58
    mov r0, #0
    bl      func_ov011_0205cff0
    mov r0, #1
    bl      func_ov011_0205cff0
    dcd     0xe3a08000
    dcd     0xe59f51f8
    dcd     0xe59f41f8
    dcd     0xe5950004
    dcd     0xe1a09008
    dcd     0xe2800a23
    dcd     0xe5901aac
    dcd     0xe1a0a008
    dcd     0xe5801ab0
    dcd     0xe5950004
    dcd     0xe3a0b001
    dcd     0xe2800a23
    dcd     0xe5901aac
    dcd     0xe1a06008
    dcd     0xe2811094
    dcd     0xe5801aac
    dcd     0xe28d7004
    dcd     0xe5952004
    dcd     0xe0821009
    dcd     0xe19100b4
    dcd     0xe3500000
    dcd     0x0a000023
    dcd     0xe2820ead
    dcd     0xe2811801
    dcd     0xe2800a23
    dcd     0xe5911920
    dcd     0xe080000a
    bl      func_020325a0
    dcd     0xe5901004
    dcd     0xe5902000
    dcd     0xe1a00641
    dcd     0xe58d2004
    dcd     0xe58d1008
    dcd     0xe3500080
    dcd     0xca000016
    dcd     0xe5950004
    dcd     0xe2812701
    dcd     0xe0801009
    dcd     0xe2800ead
    dcd     0xe2803a23
    dcd     0xe58d2008
    dcd     0xe2810801
    dcd     0xe5901924
    dcd     0xe1a02007
    dcd     0xe083000a
    bl      func_0203257c
    dcd     0xe5950004
    dcd     0xe1a0200b
    dcd     0xe0801009
    dcd     0xe2800ead
    dcd     0xe2800a23
    dcd     0xe080000a
    dcd     0xe2811801
    dcd     0xe5911924
    bl      func_02032710
    dcd     0xe5950004
    dcd     0xe0800009
    dcd     0xe18060b4
    dcd     0xe2890d25
    dcd     0xe28a1f8e
    dcd     0xe2888001
    dcd     0xe3580002
    dcd     0xe2809801
    dcd     0xe281ab12
    dcd     0xbaffffcf
    dcd     0xe3a08000
    dcd     0xe58d8000
    dcd     0xe1a09008
    dcd     0xe28d5004
    dcd     0xe3a0b001
    dcd     0xe3a04701
    dcd     0xe3a0a000
    dcd     0xe2644000
    dcd     0xe59f00d8
    dcd     0xe5901004
    dcd     0xe0880001
    dcd     0xe080010a
    dcd     0xe2800801
    dcd     0xe2811ead
    dcd     0xe590791c
    dcd     0xe2816a23
    dcd     0xe1a01007
    dcd     0xe0860009
    bl      func_02032748
    dcd     0xe3500000
    dcd     0x0a000012
    dcd     0xe1a01007
    dcd     0xe0860009
    bl      func_020325a0
    dcd     0xe8900006
    dcd     0xe58d1004
    dcd     0xe24210ae
    dcd     0xe2411c17
    dcd     0xe58d1008
    dcd     0xe0860009
    dcd     0xe1a01007
    dcd     0xe1a02005
    bl      func_0203257c
    dcd     0xe59d0008
    dcd     0xe1a01007
    dcd     0xe1500004
    dcd     0xc1a0200b
    dcd     0xd3a02000
    dcd     0xe0860009
    bl      func_02032710
    dcd     0xe28aa001
    dcd     0xe35a0004
    dcd     0xbaffffdc
    dcd     0xe59d0000
    dcd     0xe2881d25
    dcd     0xe2800001
    dcd     0xe2892f8e
    dcd     0xe58d0000
    dcd     0xe3500002
    dcd     0xe2818801
    dcd     0xe2829b12
    dcd     0xbaffffd0
    dcd     0xe59f0028
    dcd     0xe5900004
    dcd     0xe2800ead
    dcd     0xe2800a23
    bl      func_0203256c
    dcd     0xe59f0014
    dcd     0xe5900004
    dcd     0xe2800f42
    dcd     0xe2800ba1
    bl      func_0203256c
    dcd     0xe28dd00c
    dcd     0xe8bd8ff0
    dcd     data_ov011_0205e960
    dcd     0x0001092e
}
