extern void MIi_CpuCopy32(void);
extern void GFXi_EnqueueCommand(void);
extern void data_ov011_0205e960(void);

asm void func_ov011_0205b814(void)
{
    dcd     0xe92d47f0
    dcd     0xe59f40d0
    dcd     0xe1a05000
    dcd     0xe0060495
    dcd     0xe59f00c8
    dcd     0xe59d8020
    dcd     0xe5904004
    dcd     0xe203701f
    dcd     0xe0840006
    dcd     0xe590001c
    dcd     0xe2843014
    dcd     0xe1d040b2
    dcd     0xe0836006
    dcd     0xe2863f42
    dcd     0xe590a014
    dcd     0xe0291492
    dcd     0xe1a08d88
    dcd     0xe0871b28
    dcd     0xe3540020
    dcd     0xe1d000b0
    dcd     0x83a04020
    dcd     0xe2833b02
    dcd     0xe08a8309
    dcd     0xe0839301
    dcd     0xe1520000
    dcd     0xa8bd87f0
    dcd     0xe3520000
    dcd     0xb8bd87f0
    dcd     0xe0870004
    dcd     0xe3500020
    dcd     0x8a000004
    dcd     0xe1a00008
    dcd     0xe1a01009
    dcd     0xe1a02304
    bl      MIi_CpuCopy32
    dcd     0xea000009
    dcd     0xe267a020
    dcd     0xe1a0230a
    dcd     0xe1a00008
    dcd     0xe1a01009
    bl      MIi_CpuCopy32
    dcd     0xe044200a
    dcd     0xe0491307
    dcd     0xe088030a
    dcd     0xe1a02302
    bl      MIi_CpuCopy32
    dcd     0xe3550000
    dcd     0x03a00006
    dcd     0xe2861f42
    dcd     0xe2812b02
    dcd     0x13a00016
    dcd     0xe3a01000
    dcd     0xe3a03801
    bl      GFXi_EnqueueCommand
    dcd     0xe8bd87f0
    dcd     0x00010940
    dcd     data_ov011_0205e960
}
