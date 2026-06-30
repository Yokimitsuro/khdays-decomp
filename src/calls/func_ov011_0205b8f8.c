extern void MIi_CpuCopy32(void);
extern void GFXi_EnqueueCommand(void);
extern void data_ov011_0205e960(void);

asm void func_ov011_0205b8f8(void)
{
    dcd     0xe92d4ff8
    dcd     0xe24dd008
    dcd     0xe59f40e4
    dcd     0xe58d0000
    dcd     0xe0060490
    dcd     0xe59f00dc
    dcd     0xe1a04d83
    dcd     0xe5903004
    dcd     0xe2830018
    dcd     0xe0805006
    dcd     0xe5957004
    dcd     0xe2833014
    dcd     0xe0833006
    dcd     0xe1d700b2
    dcd     0xe1d7a0b0
    dcd     0xe58d3004
    dcd     0xe0261092
    dcd     0xe2833f42
    dcd     0xe5972014
    dcd     0xe2833b02
    dcd     0xe35a0020
    dcd     0x83a0a020
    dcd     0xe1510000
    dcd     0xe0826306
    dcd     0xe0837aa4
    dcd     0xa28dd008
    dcd     0xa8bd8ff8
    dcd     0xe3510000
    dcd     0xb28dd008
    dcd     0xb8bd8ff8
    dcd     0xe35a0000
    dcd     0xe59d9030
    dcd     0xe3a08000
    dcd     0x9a00000e
    dcd     0xe1a04008
    dcd     0xe3a0b040
    dcd     0xe3590020
    dcd     0x21a09004
    dcd     0xe1a00006
    dcd     0xe1a0200b
    dcd     0xe0871589
    bl      MIi_CpuCopy32
    dcd     0xe5950004
    dcd     0xe2888001
    dcd     0xe1d000b2
    dcd     0xe158000a
    dcd     0xe2899001
    dcd     0xe0866300
    dcd     0x3afffff2
    dcd     0xe59d0000
    dcd     0xe59d1004
    dcd     0xe3500000
    dcd     0x03a00006
    dcd     0xe2811f42
    dcd     0xe2812b02
    dcd     0x13a00016
    dcd     0xe3a01000
    dcd     0xe3a03801
    bl      GFXi_EnqueueCommand
    dcd     0xe28dd008
    dcd     0xe8bd8ff8
    dcd     0x00010940
    dcd     data_ov011_0205e960
}
