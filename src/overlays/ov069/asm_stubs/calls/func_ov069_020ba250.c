extern void func_ov069_020b9fe0(void);
extern void func_ov069_020b88c0(void);
extern void func_020342b4(void);
extern void func_02034150(void);
extern void NNS_FndGetNextListObject(void);
extern void func_ov069_020b9734(void);
extern void MIi_CpuCopy32(void);
extern void func_ov069_020b9ca8(void);
extern void func_ov069_020b894c(void);
extern void func_02034258(void);

asm void func_ov069_020ba250(void)
{
    dcd     0xe92d4ff0
    dcd     0xe24dd024
    dcd     0xe1a04000
    dcd     0xe1a07001
    dcd     0xe1a06002
    bl      func_ov069_020b9fe0
    mov r0, #0
    bl      func_ov069_020b88c0
    dcd     0xe3a01000
    dcd     0xe58410f4
    dcd     0xe58410f0
    dcd     0xe58d0008
    dcd     0xe58410e8
    bl      func_020342b4
    dcd     0xe3500000
    dcd     0x1a000004
    dcd     0xe59d0008
    dcd     0xe3a0100e
    bl      func_02034150
    mov r0, #1
    dcd     0xe58400f4
    dcd     0xe3a00014
    bl      func_020342b4
    dcd     0xe3500000
    dcd     0x1a000004
    dcd     0xe3a00014
    dcd     0xe3a0100e
    bl      func_02034150
    mov r0, #1
    dcd     0xe58400f0
    dcd     0xe3a00013
    bl      func_020342b4
    dcd     0xe3500000
    dcd     0x1a000004
    dcd     0xe3a00013
    dcd     0xe3a0100e
    bl      func_02034150
    mov r0, #1
    dcd     0xe58400e8
    dcd     0xe1a00006
    dcd     0xe3a01000
    bl      NNS_FndGetNextListObject
    dcd     0xe1b05000
    dcd     0x0a00000e
    dcd     0xe3a080a0
    dcd     0xe1d530ba
    dcd     0xe1a00004
    dcd     0xe1a02005
    dcd     0xe0217893
    bl      func_ov069_020b9734
    dcd     0xe1d510b8
    dcd     0xe5942000
    dcd     0xe1a00006
    dcd     0xe0822001
    dcd     0xe1a01005
    dcd     0xe5842000
    bl      NNS_FndGetNextListObject
    dcd     0xe1b05000
    dcd     0x1afffff1
    dcd     0xe28d100c
    dcd     0xe28400cc
    dcd     0xe3a02018
    bl      MIi_CpuCopy32
    dcd     0xe28d600c
    dcd     0xe3a05000
    dcd     0xe58d6000
    dcd     0xe0840185
    dcd     0xe59020cc
    dcd     0xe59030d0
    dcd     0xe1a00004
    dcd     0xe1a01007
    bl      func_ov069_020b9ca8
    dcd     0xe2855001
    dcd     0xe3550003
    dcd     0xe2866008
    dcd     0xe28770a0
    dcd     0xbafffff3
    mov r0, #0
    dcd     0xe58d0004
    dcd     0xe5840004
    dcd     0xe3a0e001
    dcd     0xe1a0c000
    dcd     0xe1a02000
    dcd     0xe1a01000
    dcd     0xe59d0004
    dcd     0xe3a0b000
    dcd     0xe28d300c
    dcd     0xe1a0a00b
    dcd     0xe0836180
    dcd     0xe3a09000
    dcd     0xe089300a
    dcd     0xe1a0531c
    dcd     0xe8960081
    dcd     0xe000831e
    dcd     0xe2630020
    dcd     0xe185503e
    dcd     0xe2430020
    dcd     0xe185501e
    dcd     0xe0070005
    dcd     0xe1500002
    dcd     0x01580001
    dcd     0x15940004
    dcd     0xe2899001
    dcd     0x12800001
    dcd     0x15840004
    dcd     0xe3590005
    dcd     0xbaffffee
    dcd     0xe28bb001
    dcd     0xe35b0008
    dcd     0xe28aa005
    dcd     0xbaffffe9
    dcd     0xe59d0004
    dcd     0xe2800001
    dcd     0xe58d0004
    dcd     0xe3500003
    dcd     0xbaffffdf
    dcd     0xe2840008
    dcd     0xe3a01000
    bl      NNS_FndGetNextListObject
    dcd     0xe1b01000
    dcd     0x0a00000b
    dcd     0xe3a06001
    dcd     0xe1a05006
    dcd     0xe5910014
    dcd     0xe3500000
    dcd     0x05816014
    dcd     0xe5910010
    dcd     0xe3500000
    dcd     0xe2840008
    dcd     0x05815010
    bl      NNS_FndGetNextListObject
    dcd     0xe1b01000
    dcd     0x1afffff5
    dcd     0xe284002c
    bl      func_ov069_020b894c
    dcd     0xe59400e8
    dcd     0xe3500000
    dcd     0x0a000003
    dcd     0xe3a00013
    bl      func_02034258
    mov r0, #0
    dcd     0xe58400e8
    dcd     0xe59400f0
    dcd     0xe3500000
    dcd     0x0a000003
    dcd     0xe3a00014
    bl      func_02034258
    mov r0, #0
    dcd     0xe58400f0
    dcd     0xe59400f4
    dcd     0xe3500000
    dcd     0x028dd024
    dcd     0x08bd8ff0
    dcd     0xe59d0008
    bl      func_02034258
    mov r0, #0
    dcd     0xe58400f4
    dcd     0xe28dd024
    dcd     0xe8bd8ff0
}
