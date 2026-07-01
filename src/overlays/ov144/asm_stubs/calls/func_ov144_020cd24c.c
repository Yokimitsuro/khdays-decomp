extern void func_ov107_020c5c54(void);
extern void func_ov144_020cc970(void);
extern void VEC_Subtract(void);
extern void func_020050b4(void);
extern void func_0203c634(void);

asm void func_ov144_020cd24c(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd00c
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe5940000
    dcd     0xe1d006b0
    dcd     0xe1a00c00
    dcd     0xe1a00c20
    dcd     0xe3100001
    dcd     0x028dd00c
    dcd     0x08bd8030
    mov r0, #0
    dcd     0xe5840044
    dcd     0xe5840048
    dcd     0xe584004c
    dcd     0xe5941000
    dcd     0xe5940048
    dcd     0xe0810100
    dcd     0xe59003c0
    dcd     0xe584003c
    dcd     0xe5940000
    dcd     0xe59003e8
    dcd     0xe5840034
    dcd     0xe5840030
    dcd     0xe5940000
    dcd     0xe590139c
    dcd     0xe3510000
    dcd     0x159003b8
    dcd     0x13500000
    dcd     0x0a00000a
    dcd     0xe5940044
    dcd     0xe284300c
    dcd     0xe0810200
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5941000
    dcd     0xe5940044
    dcd     0xe591139c
    dcd     0xe0810200
    dcd     0xe590000c
    dcd     0xea000004
    dcd     0xe5940008
    dcd     0xe284300c
    dcd     0xe8900007
    dcd     0xe8830007
    mov r0, #0
    dcd     0xe5840040
    dcd     0xe5940000
    dcd     0xe2801feb
    bl      func_ov107_020c5c54
    dcd     0xe1a00004
    dcd     0xe3a01000
    bl      func_ov144_020cc970
    dcd     0xe3500000
    dcd     0x0a00000e
    dcd     0xe5941008
    dcd     0xe28d2000
    dcd     0xe284000c
    bl      VEC_Subtract
    dcd     0xe59d0000
    dcd     0xe59d1008
    bl      func_020050b4
    dcd     0xe5840034
    dcd     0xe5840030
    mov r0, #1
    dcd     0xe584004c
    dcd     0xe5940000
    dcd     0xe3a01007
    dcd     0xe5c011c7
    dcd     0xea000003
    dcd     0xe5941000
    dcd     0xe2810c01
    dcd     0xe1d00cd9
    dcd     0xe5c101c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd8030
}
