extern void VEC_Subtract(void);
extern void data_02041dc8(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_0203c634(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020c9264(void);

asm void func_ov174_020d20b8(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe59f0098
    dcd     0xe284302c
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5941010
    dcd     0xe3510000
    dcd     0x0a000006
    dcd     0xe5940000
    dcd     0xe1a02003
    dcd     0xe2800074
    dcd     0xe2811074
    bl      VEC_Subtract
    mov r0, #0
    dcd     0xe5840030
    dcd     0xe284002c
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe284102c
    dcd     0xe1a02001
    dcd     0xe3a00b02
    bl      func_01ffa724
    dcd     0xe5940000
    dcd     0xe3a01006
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe5940000
    dcd     0xe59f1034
    dcd     0xe5943008
    dcd     0xe3a02008
    bl      func_ov107_020c5af8
    dcd     0xe3a00a06
    dcd     0xe5840058
    dcd     0xe5940000
    dcd     0xe3a0100b
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     data_02041dc8
    dcd     0x00000141
}
