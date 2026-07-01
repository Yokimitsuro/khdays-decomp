extern void func_ov107_020c0b90(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020c5c54(void);
extern void func_0203c634(void);
extern void data_02041dc8(void);

asm void func_ov298_020d53c4(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd014
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a0c000
    dcd     0xe58dc004
    dcd     0xe5940008
    dcd     0xe24d3008
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5940000
    dcd     0xe1a0100c
    dcd     0xe893000c
    bl      func_ov107_020c0b90
    dcd     0xe5940000
    dcd     0xe5943008
    dcd     0xe59f1068
    dcd     0xe3a02004
    bl      func_ov107_020c5af8
    dcd     0xe3a01000
    dcd     0xe59f005c
    dcd     0xe58d1008
    dcd     0xe59f1058
    dcd     0xe58d000c
    mov r0, #1
    dcd     0xe58d1010
    dcd     0xe5840084
    dcd     0xe59f0048
    dcd     0xe2843010
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5940000
    dcd     0xe28d1008
    bl      func_ov107_020c5c54
    dcd     0xe3a02000
    dcd     0xe5842038
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd014
    dcd     0xe8bd8030
    dcd     0x00000177
    dcd     0xffffda42
    dcd     0x0002d077
    dcd     data_02041dc8
}
