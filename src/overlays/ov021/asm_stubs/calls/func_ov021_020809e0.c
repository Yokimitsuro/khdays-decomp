extern char data_0204c240[];
extern void func_0202aa9c(void);
extern void func_0202bedc(void);
extern void func_02030788(void);
extern void func_ov002_0206bbb8(void);
extern void func_ov002_020766e0(void);
extern void func_ov002_0207687c(void);
extern void func_ov002_0207cea4(void);
extern void func_ov021_020804d0(void);
extern void func_ov021_02080758(void);
extern void func_ov021_02080828(void);
extern void func_ov021_02080c40(void);

asm void func_ov021_020809e0(void)
{
    dcd     0xe92d4010
    dcd     0xe24dd008
    dcd     0xe1a04000
    bl      func_ov002_0207687c
    dcd     0xe1a01000
    dcd     0xe1a00004
    bl      func_ov021_020804d0
    dcd     0xe5d402b4
    dcd     0xe3500000
    dcd     0x0a000004
    dcd     0xe3500002
    dcd     0x0a000014
    dcd     0xe3500003
    dcd     0x0a000034
    dcd     0xea00003c
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000039
    dcd     0xe1a00004
    bl      func_ov021_02080758
    dcd     0xe3500000
    dcd     0xba000035
    dcd     0xe5cd0004
    dcd     0xe3a03000
    dcd     0xe28d1000
    dcd     0xe1a00004
    dcd     0xe3a02006
    dcd     0xe5cd3000
    bl      func_ov002_020766e0
    dcd     0xe3500000
    dcd     0x13a00001
    dcd     0x15c402b4
    dcd     0xea00002a
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000013
    dcd     0xe59402b8
    dcd     0xe3a01003
    dcd     0xe3500000
    dcd     0xe2840c02
    dcd     0xc3a0200a
    dcd     0xe1d00bdc
    dcd     0xd3a02008
    bl      func_ov002_0206bbb8
    dcd     0xe59f00a4
    dcd     0xe5d00000
    dcd     0xe3100004
    dcd     0x0a000007
    dcd     0xe59402b8
    dcd     0xe3a01007
    dcd     0xe3500000
    dcd     0xe2840c02
    dcd     0xc3a02014
    dcd     0xe1d00bdc
    dcd     0xd3a02005
    bl      func_ov002_0206bbb8
    dcd     0xe1a00004
    bl      func_ov021_02080c40
    dcd     0xe3a00003
    dcd     0xe5c402b4
    dcd     0xe1d401b2
    dcd     0xe3100004
    dcd     0x0a00000c
    dcd     0xe2840f49
    dcd     0xe3a01000
    bl      func_0202bedc
    dcd     0xea000008
    dcd     0xe1a00004
    bl      func_ov021_02080828
    dcd     0xe3500000
    dcd     0x0a000004
    dcd     0xe3a00004
    dcd     0xe5c402b4
    dcd     0xe28dd008
    dcd     0xe59f0030
    dcd     0xe8bd8010
    dcd     0xe5d402b4
    dcd     0xe3500004
    dcd     0x0a000004
    dcd     0xe1d401b2
    dcd     0xe3100004
    dcd     0x0a000001
    dcd     0xe284001c
    bl      func_0202aa9c
    mov r0, #0
    dcd     0xe28dd008
    dcd     0xe8bd8010
    dcd     data_0204c240
    dcd     func_ov002_0207cea4
}
