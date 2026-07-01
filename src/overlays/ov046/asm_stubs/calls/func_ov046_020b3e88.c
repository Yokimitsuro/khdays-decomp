extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void VEC_Add(void);
extern void VEC_Mag(void);
extern void VEC_Subtract(void);
extern char data_0203d210[];
extern char data_ov046_020b4b40[];
extern void func_01ffd0e8(void);
extern void func_0202c268(void);
extern void func_ov022_02091324(void);
extern void func_ov022_020ad0c0(void);
extern void func_ov022_020ad114(void);

asm void func_ov046_020b3e88(void)
{
    dcd     0xe92d40f8
    dcd     0xe24dd080
    dcd     0xe1a05000
    dcd     0xe5950020
    dcd     0xe59f11e0
    dcd     0xe1d028b0
    dcd     0xe285008c
    dcd     0xe28d403c
    dcd     0xe2422902
    dcd     0xe1a03802
    dcd     0xe2800b01
    dcd     0xe591c000
    dcd     0xe8900007
    dcd     0xe8840007
    dcd     0xe1a00005
    dcd     0xe28c4db2
    dcd     0xe1a07823
    dcd     0xe3a06000
    bl      func_ov022_020ad114
    dcd     0xe3500000
    dcd     0x0a00000e
    dcd     0xe1a00005
    bl      func_ov022_020ad0c0
    dcd     0xe28d103c
    dcd     0xe28d2000
    bl      VEC_Subtract
    dcd     0xe28d0000
    bl      VEC_Mag
    dcd     0xe3500a09
    dcd     0xca000005
    dcd     0xe1a00005
    bl      func_ov022_020ad0c0
    dcd     0xe28d3048
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe3a06001
    dcd     0xe3560000
    dcd     0x1a000018
    dcd     0xe1a00247
    dcd     0xe1a01080
    dcd     0xe2810001
    dcd     0xe59f2150
    dcd     0xe1a01081
    dcd     0xe19210f1
    dcd     0xe1a00080
    dcd     0xe19220f0
    dcd     0xe28d000c
    dcd     0xe2611000
    dcd     0xe2622000
    bl      MTX_RotY33_
    dcd     0xe3a0c000
    dcd     0xe28d0048
    dcd     0xe3a03a02
    dcd     0xe28d100c
    dcd     0xe1a02000
    dcd     0xe58dc048
    dcd     0xe58dc04c
    dcd     0xe58d3050
    bl      MTX_MultVec33
    dcd     0xe28d1048
    dcd     0xe28d003c
    dcd     0xe1a02001
    bl      VEC_Add
    dcd     0xe3a01000
    dcd     0xe2410a07
    dcd     0xe58d1030
    dcd     0xe58d1038
    dcd     0xe58d0034
    dcd     0xe1d506b6
    dcd     0xe5953020
    dcd     0xe28d1048
    dcd     0xe28d2030
    bl      func_0202c268
    dcd     0xe3500000
    dcd     0x059d004c
    dcd     0x02400a07
    dcd     0x058d004c
    dcd     0x0a000008
    dcd     0xe28d2048
    dcd     0xe590000c
    dcd     0xe28d1030
    dcd     0xe1a03002
    bl      func_01ffd0e8
    dcd     0xe59d004c
    dcd     0xe280009a
    dcd     0xe2800c01
    dcd     0xe58d004c
    dcd     0xe3a0c000
    dcd     0xe28d0048
    dcd     0xe28d3054
    dcd     0xe1cdc6b4
    dcd     0xe1cdc6b2
    dcd     0xe1cdc6b0
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe3a00007
    dcd     0xe58dc068
    dcd     0xe58dc070
    dcd     0xe58dc074
    dcd     0xe58d006c
    dcd     0xe5940124
    dcd     0xe58dc07c
    dcd     0xe58d0078
    dcd     0xe5940124
    dcd     0xe3500000
    dcd     0x0a000004
    dcd     0xe3500001
    dcd     0x0a000005
    dcd     0xe3500002
    dcd     0x0a000006
    dcd     0xea000009
    dcd     0xe3a00d66
    dcd     0xe1cd06b6
    dcd     0xea000006
    dcd     0xe3a00c22
    dcd     0xe1cd06b6
    dcd     0xea000003
    dcd     0xe3a01b09
    mov r0, #1
    dcd     0xe1cd16b6
    dcd     0xe58d007c
    dcd     0xe28d1054
    dcd     0xe1a00005
    bl      func_ov022_02091324
    dcd     0xe28dd080
    dcd     0xe8bd80f8
    dcd     data_ov046_020b4b40
    dcd     data_0203d210
}
