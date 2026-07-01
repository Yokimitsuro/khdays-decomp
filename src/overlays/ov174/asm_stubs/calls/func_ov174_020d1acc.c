extern void func_0203c634(void);
extern void func_ov107_020c0b90(void);
extern void func_ov107_020c5af8(void);
extern void func_ov174_020d190c(void);

asm void func_ov174_020d1acc(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd008
    dcd     0xe1a04000
    dcd     0xe5945004
    dcd     0xe5951010
    dcd     0xe3510000
    dcd     0x0a000006
    dcd     0xe3a01000
    dcd     0xe5851048
    dcd     0xe1d412d0
    dcd     0xe59f2068
    bl      func_0203c634
    dcd     0xe28dd008
    dcd     0xe8bd8038
    mov r0, #0
    dcd     0xe58d0004
    dcd     0xe5950008
    dcd     0xe24d3008
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5950000
    dcd     0xe3a01005
    dcd     0xe893000c
    bl      func_ov107_020c0b90
    dcd     0xe5950000
    dcd     0xe5953008
    dcd     0xe59f102c
    dcd     0xe3a02007
    bl      func_ov107_020c5af8
    dcd     0xe5950000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d412d0
    dcd     0xe1a00004
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd008
    dcd     0xe8bd8038
    dcd     func_ov174_020d190c
    dcd     0x00000141
}
