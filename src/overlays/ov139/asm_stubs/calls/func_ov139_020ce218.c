extern void func_ov107_020c9264(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_ov107_020c5af8(void);
extern void func_0203c634(void);
extern void data_02042258(void);
extern void func_ov139_020ce2d8(void);

asm void func_ov139_020ce218(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01009
    dcd     0xe5940000
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe5941044
    dcd     0xe3510000
    dcd     0x0a000004
    dcd     0xe5940048
    dcd     0xe2811e19
    dcd     0xe284202c
    bl      VEC_Subtract
    dcd     0xea000003
    dcd     0xe2840020
    dcd     0xe284302c
    dcd     0xe8900007
    dcd     0xe8830007
    mov r0, #0
    dcd     0xe5840030
    dcd     0xe284002c
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe3500000
    dcd     0x1a000003
    dcd     0xe59f0044
    dcd     0xe284302c
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe3a00b02
    dcd     0xe5840038
    mov r0, #0
    dcd     0xe5c40054
    dcd     0xe584003c
    dcd     0xe5940000
    dcd     0xe594304c
    dcd     0xe59f101c
    dcd     0xe3a02008
    bl      func_ov107_020c5af8
    dcd     0xe1d512d0
    dcd     0xe59f2010
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     data_02042258
    dcd     0x0000011f
    dcd     func_ov139_020ce2d8
}
