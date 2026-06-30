extern void MI_Copy48B(void);
extern void func_01ff9f00(void);
extern void func_0201571c(void);
extern void func_020279e0(void);

asm void func_ov077_020b9310(void)
{
    dcd     0xe92d4018
    dcd     0xe24dd00c
    dcd     0xe1a04001
    dcd     0xe5941000
    dcd     0xe3510002
    dcd     0x13510003
    dcd     0x128dd00c
    dcd     0x18bd8018
    dcd     0xe2800f56
    dcd     0xe2800b01
    dcd     0xe2841084
    bl      MI_Copy48B
    dcd     0xe5940028
    dcd     0xe28d1000
    dcd     0xe590301c
    dcd     0xe3a0001b
    dcd     0xe3a02003
    dcd     0xe58d3000
    dcd     0xe58d3004
    dcd     0xe58d3008
    bl      func_01ff9f00
    bl      func_0201571c
    dcd     0xe2841084
    dcd     0xe3a00017
    dcd     0xe3a0200c
    bl      func_01ff9f00
    dcd     0xe2840024
    bl      func_020279e0
    dcd     0xe28dd00c
    dcd     0xe8bd8018
}
