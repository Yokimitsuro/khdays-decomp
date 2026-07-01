extern void VEC_Add(void);
extern void func_01ff8e94(void);
extern void func_02033d0c(void);
extern void func_ov022_020914a0(void);
extern void func_ov022_02091540(void);
extern void func_ov022_0209198c(void);
extern void func_ov022_02091b48(void);

asm void func_ov054_020b6b2c(void)
{
    dcd     0xe92d41f0
    dcd     0xe24dd018
    dcd     0xe1a07001
    dcd     0xe1a08000
    dcd     0xe5984008
    dcd     0xe5975138
    dcd     0xe1a06002
    dcd     0xe28700cc
    dcd     0xe28d300c
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe28d0000
    dcd     0xe1a01008
    dcd     0xe1a02007
    dcd     0xe1a03006
    bl      func_ov022_0209198c
    dcd     0xe1a00008
    dcd     0xe1a01007
    dcd     0xe28d200c
    dcd     0xe28d3000
    bl      func_ov022_02091b48
    dcd     0xe28d000c
    dcd     0xe28d1000
    dcd     0xe1a02000
    bl      VEC_Add
    dcd     0xe28d000c
    dcd     0xe28730cc
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe1a01006
    dcd     0xe2870028
    bl      func_ov022_02091540
    dcd     0xe3500000
    dcd     0x0a000006
    dcd     0xe1d712fa
    dcd     0xe3510000
    dcd     0x13510002
    dcd     0x1a000002
    dcd     0xe1a00007
    dcd     0xe2811001
    bl      func_ov022_020914a0
    dcd     0xe1d700d2
    dcd     0xe3500003
    dcd     0x0a00000b
    dcd     0xe28d100c
    dcd     0xe2870010
    bl      func_01ff8e94
    dcd     0xe5951014
    dcd     0xe1500001
    dcd     0xca000003
    dcd     0xe5971004
    dcd     0xe5950018
    dcd     0xe1510000
    dcd     0xba000001
    dcd     0xe3a00004
    dcd     0xe5c70002
    dcd     0xe1d700d2
    dcd     0xe3500002
    dcd     0x0a000011
    dcd     0xe2840a02
    dcd     0xe5d006c4
    dcd     0xe3500004
    dcd     0x1a000008
    dcd     0xe5d40694
    dcd     0xe1a00f80
    dcd     0xe1b00fa0
    dcd     0x0a000004
    dcd     0xe28d200c
    dcd     0xe3a000d3
    dcd     0xe3a01006
    dcd     0xe3a03000
    bl      func_02033d0c
    dcd     0xe3a00004
    dcd     0xe5c70002
    dcd     0xe595103c
    dcd     0xe1a00007
    bl      func_ov022_020914a0
    mov r0, #0
    dcd     0xe28dd018
    dcd     0xe8bd81f0
}
