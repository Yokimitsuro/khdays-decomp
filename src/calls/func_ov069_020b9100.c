extern void MI_CpuFill8(void);
extern void NNS_FndInitList(void);
extern void NNS_FndGetNextListObject(void);
extern void NNS_FndAppendListObject(void);
extern void func_ov069_020b90b4(void);
extern void func_ov069_020b89f8(void);
extern void func_ov069_020b8a90(void);
extern void func_ov069_020b8b98(void);

asm void func_ov069_020b9100(void)
{
    dcd     0xe92d4ff8
    dcd     0xe24dd0b8
    dcd     0xe1a0a000
    dcd     0xe1a09001
    dcd     0xe3a01000
    dcd     0xe3e03000
    dcd     0xe28d0018
    dcd     0xe3a020a0
    dcd     0xe58d1008
    dcd     0xe58d3004
    bl      MI_CpuFill8
    dcd     0xe28d000c
    dcd     0xe3a01004
    bl      NNS_FndInitList
    dcd     0xe3a05000
    dcd     0xe59a40f8
    dcd     0xe28d0008
    dcd     0xe1a02005
    dcd     0xe3a01014
    dcd     0xe3a0300e
    dcd     0xe12fff34
    dcd     0xe59d1008
    dcd     0xe5990000
    dcd     0xe5911020
    dcd     0xe1510000
    dcd     0x1a00004e
    dcd     0xe28d000c
    dcd     0xe3a01004
    bl      NNS_FndInitList
    dcd     0xe59d0008
    dcd     0xe3a07000
    dcd     0xe5902024
    dcd     0xe5993008
    dcd     0xe1a01007
    dcd     0xe2890010
    dcd     0xe00b0293
    bl      NNS_FndGetNextListObject
    dcd     0xe1d020b0
    dcd     0xe28d1018
    dcd     0xe1cd21b8
    dcd     0xe1d020b2
    dcd     0xe28d000c
    dcd     0xe1cd21ba
    bl      NNS_FndAppendListObject
    dcd     0xe1a08009
    dcd     0xe3a04001
    dcd     0xe1a06007
    dcd     0xe59d0008
    dcd     0xe0800186
    dcd     0xe5900028
    dcd     0xe3500000
    dcd     0xba000009
    dcd     0xe1a01009
    bl      func_ov069_020b90b4
    dcd     0xe3500000
    dcd     0x03a04000
    dcd     0x0a000008
    dcd     0xe59d0008
    dcd     0xe59810e4
    dcd     0xe0800186
    dcd     0xe590002c
    dcd     0xe0277091
    dcd     0xe2866001
    dcd     0xe3560005
    dcd     0xe28880dc
    dcd     0xbaffffec
    dcd     0xe3540000
    dcd     0x0a000024
    dcd     0xe08b0007
    dcd     0xe28000ff
    dcd     0xe2802c0f
    dcd     0xe59d1008
    dcd     0xe1a005c2
    dcd     0xe0820a20
    dcd     0xe5912018
    dcd     0xe1a00640
    dcd     0xe3520000
    dcd     0xe1a04600
    dcd     0x0a000004
    dcd     0xe3520001
    dcd     0x0a000006
    dcd     0xe3520002
    dcd     0x0a00000b
    dcd     0xea000011
    dcd     0xe1a0000a
    dcd     0xe1a02644
    bl      func_ov069_020b89f8
    dcd     0xea00000d
    dcd     0xe3a03001
    dcd     0xe58d3000
    dcd     0xe591101c
    dcd     0xe1a0000a
    dcd     0xe1a02644
    bl      func_ov069_020b8a90
    dcd     0xea000006
    dcd     0xe3a00001
    dcd     0xe58d0000
    dcd     0xe591101c
    dcd     0xe1a0000a
    dcd     0xe1a02644
    dcd     0xe3a03000
    bl      func_ov069_020b8b98
    dcd     0xe59d0008
    dcd     0xe5900014
    dcd     0xe58d0004
    dcd     0xe59a10fc
    dcd     0xe28d0008
    dcd     0xe12fff31
    dcd     0xe2855001
    dcd     0xe3550018
    dcd     0xbaffff9f
    dcd     0xe59d0004
    dcd     0xe28dd0b8
    dcd     0xe8bd8ff8
}
