extern void func_ov107_020cab14(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);
extern void func_01ffa724(void);
extern void func_02023eb4(void);
extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void func_ov139_020cc9d4(void);
extern void func_0203c634(void);
extern void data_0203d210(void);
extern void data_ov139_020cec14(void);

asm void func_ov139_020ccd08(void)
{
    dcd     0xe92d40f8
    dcd     0xe24dd048
    dcd     0xe1a06000
    dcd     0xe5964004
    dcd     0xe3a01000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe3500000
    dcd     0x028dd048
    dcd     0xe5840004
    dcd     0x08bd80f8
    dcd     0xe594104c
    dcd     0xe28d203c
    dcd     0xe2800074
    bl      VEC_Subtract
    dcd     0xe3a00000
    dcd     0xe58d0040
    dcd     0xe28d003c
    dcd     0xe1a01000
    dcd     0xe89400a0
    bl      func_01ff8d18
    dcd     0xe5973080
    dcd     0xe5952080
    dcd     0xe59d1044
    dcd     0xe0832002
    dcd     0xe0405002
    dcd     0xe59d003c
    bl      func_020050b4
    dcd     0xe584000c
    dcd     0xe3550a02
    dcd     0xaa00001a
    dcd     0xe5942008
    dcd     0xe59f0194
    dcd     0xe59f1194
    dcd     0xe083e092
    dcd     0xe0233192
    dcd     0xe1a01fc2
    dcd     0xe0233091
    dcd     0xe29e0000
    dcd     0xe2a30b02
    dcd     0xe1a00200
    dcd     0xe1a00820
    dcd     0xe1a00240
    dcd     0xe1a02080
    dcd     0xe2820001
    dcd     0xe3a0c000
    dcd     0xe59f1164
    dcd     0xe1a02082
    dcd     0xe191e0f2
    dcd     0xe1a00080
    dcd     0xe19130f0
    dcd     0xe28d1030
    dcd     0xe24c0c01
    dcd     0xe2842014
    dcd     0xe58de030
    dcd     0xe58dc034
    dcd     0xe58d3038
    bl      func_01ffa724
    dcd     0xe3550901
    dcd     0xd5940040
    dcd     0xd3500000
    dcd     0xca000038
    dcd     0xe59f0128
    dcd     0xe28d3000
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe3a00065
    bl      func_02023eb4
    dcd     0xe594300c
    dcd     0xe59f1100
    dcd     0xe59f2100
    dcd     0xe08ce193
    dcd     0xe02cc293
    dcd     0xe1a02fc3
    dcd     0xe02cc192
    dcd     0xe2805000
    dcd     0xe29e0000
    dcd     0xe2ac0b02
    dcd     0xe1a00200
    dcd     0xe1a00820
    dcd     0xe1a00240
    dcd     0xe1a01080
    dcd     0xe2810001
    dcd     0xe59f20d0
    dcd     0xe1a01081
    dcd     0xe1a00080
    dcd     0xe19210f1
    dcd     0xe19220f0
    dcd     0xe28d000c
    bl      MTX_RotY33_
    dcd     0xe28d0000
    dcd     0xe28d100c
    dcd     0xe1a02000
    bl      MTX_MultVec33
    dcd     0xe3550046
    dcd     0xaa00000d
    dcd     0xe28d1000
    dcd     0xe1a00006
    bl      func_ov139_020cc9d4
    dcd     0xe3500000
    dcd     0x1a000008
    dcd     0xe5940000
    dcd     0xe3a01005
    dcd     0xe5c011c7
    dcd     0xe1d612d0
    dcd     0xe1a00006
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd048
    dcd     0xe8bd80f8
    dcd     0xe5940000
    dcd     0xe3a01006
    dcd     0xe5c011c7
    dcd     0xe1d612d0
    dcd     0xe1a00006
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd048
    dcd     0xe8bd80f8
    dcd     0xe5941000
    dcd     0xe59102d8
    dcd     0xe1550000
    dcd     0xa28dd048
    dcd     0xa8bd80f8
    dcd     0xe3550901
    dcd     0xb28dd048
    dcd     0xb8bd80f8
    dcd     0xe3a00004
    dcd     0xe5c101c7
    dcd     0xe1d612d0
    dcd     0xe1a00006
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd048
    dcd     0xe8bd80f8
    dcd     0x60db9391
    dcd     0x000028be
    dcd     data_0203d210
    dcd     data_ov139_020cec14
}
