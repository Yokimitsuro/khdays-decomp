extern void FX_Atan2(void);
extern void VEC_Add(void);
extern void VEC_Mag(void);
extern void VEC_Subtract(void);
extern char data_0203d210[];
extern char data_ov079_020b9a00[];
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_02030788(void);
extern void func_ov022_020a35f4(void);
extern void func_ov022_020ad0c0(void);
extern void func_ov022_020ad114(void);

asm void func_ov079_020b964c(void)
{
    dcd     0xe92d41f8
    dcd     0xe24dd024
    dcd     0xe59f1268
    dcd     0xe3a05000
    dcd     0xe5911000
    dcd     0xe1a08000
    dcd     0xe2810a02
    dcd     0xe1a06005
    dcd     0xe5904d70
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe2880064
    dcd     0xe5982464
    dcd     0xe5901404
    dcd     0xe3822801
    dcd     0xe5882464
    dcd     0xe3811000
    dcd     0xe5801404
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe288006c
    dcd     0xe598246c
    dcd     0xe5901404
    dcd     0xe3822801
    dcd     0xe588246c
    dcd     0xe3811000
    dcd     0xe5801404
    mov r0, #0
    dcd     0xe58d0014
    dcd     0xe58d0010
    dcd     0xe58d000c
    dcd     0xe58d0020
    dcd     0xe58d001c
    dcd     0xe58d0018
    dcd     0xe5982464
    dcd     0xe5981468
    dcd     0xe2022000
    dcd     0xe2011002
    dcd     0xe3510000
    dcd     0x03520000
    dcd     0x0a000051
    dcd     0xe3a01a02
    dcd     0xe1a00008
    dcd     0xe58814b4
    bl      func_ov022_020ad114
    dcd     0xe3500000
    dcd     0x1a000015
    dcd     0xe5981020
    dcd     0xe0840fa4
    dcd     0xe1d118b0
    dcd     0xe3a02000
    dcd     0xe59f41a0
    dcd     0xe2411902
    dcd     0xe1a01801
    dcd     0xe1a01821
    dcd     0xe1a01241
    dcd     0xe1a03081
    dcd     0xe2831001
    dcd     0xe1a03083
    dcd     0xe1a01081
    dcd     0xe19430f3
    dcd     0xe19410f1
    dcd     0xe58d2010
    dcd     0xe2632000
    dcd     0xe2611000
    dcd     0xe58d200c
    dcd     0xe58d1014
    dcd     0xe1a040c0
    dcd     0xea00002d
    dcd     0xe1a00008
    bl      func_ov022_020ad0c0
    dcd     0xe288108c
    dcd     0xe28d2018
    dcd     0xe2811b01
    bl      VEC_Subtract
    dcd     0xe28d0018
    bl      VEC_Mag
    dcd     0xe1a07000
    dcd     0xe3570b06
    dcd     0xba000020
    dcd     0xe59d0018
    dcd     0xe59d1020
    dcd     0xe2600000
    dcd     0xe2611000
    bl      FX_Atan2
    dcd     0xe5982020
    dcd     0xe1a00800
    dcd     0xe5921000
    dcd     0xe1a00820
    dcd     0xe3110020
    dcd     0x1a000004
    dcd     0xe2800902
    dcd     0xe1c208b0
    dcd     0xe1d200b4
    dcd     0xe3800020
    dcd     0xe1c200b4
    dcd     0xe1570004
    dcd     0xaa000002
    dcd     0xe28d0018
    bl      VEC_Mag
    dcd     0xe1a04000
    dcd     0xe28d0018
    bl      VEC_Mag
    dcd     0xe3500000
    dcd     0xe28d0018
    dcd     0x1a000003
    dcd     0xe28d300c
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xea000004
    dcd     0xe28d100c
    bl      func_01ff8d18
    dcd     0xea000001
    dcd     0xe3a04000
    dcd     0xe3a05001
    dcd     0xe28d100c
    dcd     0xe1a00004
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe59d0010
    dcd     0xe3500000
    dcd     0x15880058
    dcd     0xea000009
    dcd     0xe5981024
    dcd     0xe3110004
    dcd     0x1a000006
    dcd     0xe5982000
    dcd     0xe5981004
    dcd     0xe1822000
    dcd     0xe5882000
    dcd     0xe3811901
    dcd     0xe5881004
    dcd     0xe5880058
    dcd     0xe28d000c
    dcd     0xe28d3000
    dcd     0xe8900007
    dcd     0xe8830007
    mov r0, #0
    dcd     0xe2882098
    dcd     0xe58d0004
    dcd     0xe2820b01
    dcd     0xe1a01003
    dcd     0xe2822b01
    bl      VEC_Add
    dcd     0xe59804cc
    dcd     0xe3500906
    dcd     0xaa000001
    dcd     0xe3550000
    dcd     0x0a000003
    dcd     0xe1a00008
    dcd     0xe3a01022
    bl      func_ov022_020a35f4
    dcd     0xe1a06000
    dcd     0xe1a00006
    dcd     0xe28dd024
    dcd     0xe8bd81f8
    dcd     data_ov079_020b9a00
    dcd     data_0203d210
}
