extern void FX_Atan2(void);
extern void VEC_Add(void);
extern void VEC_Mag(void);
extern void VEC_Subtract(void);
extern char data_0203d210[];
extern char data_ov090_020bcc00[];
extern void func_01ffa724(void);
extern void func_02030788(void);
extern void func_ov022_020a35f4(void);
extern void func_ov022_020ad0c0(void);
extern void func_ov022_020ad114(void);

asm void func_ov090_020bbab0(void)
{
    dcd     0xe92d41f8
    dcd     0xe24dd024
    dcd     0xe59f11f0
    dcd     0xe1a08000
    dcd     0xe5910000
    dcd     0xe3a04000
    dcd     0xe2800a02
    dcd     0xe5906cf8
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
    dcd     0xe3a01000
    dcd     0xe1a00008
    dcd     0xe58d1014
    dcd     0xe58d1010
    dcd     0xe58d100c
    bl      func_ov022_020ad114
    dcd     0xe3500000
    dcd     0x1a000005
    dcd     0xe5980020
    dcd     0xe1d008b0
    dcd     0xe2400902
    dcd     0xe1a00800
    dcd     0xe1a05820
    dcd     0xea000027
    dcd     0xe1a00008
    bl      func_ov022_020ad0c0
    dcd     0xe288108c
    dcd     0xe28d2018
    dcd     0xe2811b01
    bl      VEC_Subtract
    dcd     0xe28d0018
    bl      VEC_Mag
    dcd     0xe59f1134
    dcd     0xe1a07000
    dcd     0xe1570001
    dcd     0xba000015
    dcd     0xe59d0018
    dcd     0xe59d1020
    dcd     0xe2600000
    dcd     0xe2611000
    bl      FX_Atan2
    dcd     0xe5982020
    dcd     0xe1a00800
    dcd     0xe5921000
    dcd     0xe1a05820
    dcd     0xe3110020
    dcd     0x1a000004
    dcd     0xe2850902
    dcd     0xe1c208b0
    dcd     0xe1d200b4
    dcd     0xe3800020
    dcd     0xe1c200b4
    dcd     0xe1570006
    dcd     0xaa000009
    dcd     0xe28d0018
    bl      VEC_Mag
    dcd     0xe1a06000
    dcd     0xea000005
    dcd     0xe5980020
    dcd     0xe3a06000
    dcd     0xe1d008b0
    dcd     0xe2400902
    dcd     0xe1a00800
    dcd     0xe1a05820
    dcd     0xe3560000
    dcd     0xda000011
    dcd     0xe1a00245
    dcd     0xe1a02080
    dcd     0xe2820001
    dcd     0xe59f10a4
    dcd     0xe1a02082
    dcd     0xe1a00080
    dcd     0xe19120f2
    dcd     0xe19100f0
    dcd     0xe3a03000
    dcd     0xe2627000
    dcd     0xe2605000
    dcd     0xe28d100c
    dcd     0xe1a00006
    dcd     0xe1a02001
    dcd     0xe58d700c
    dcd     0xe58d5014
    dcd     0xe58d3010
    bl      func_01ffa724
    dcd     0xe59f106c
    dcd     0xe28d000c
    dcd     0xe5881058
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
    dcd     0xe5981668
    dcd     0xe1a00008
    dcd     0xe12fff31
    dcd     0xe59804cc
    dcd     0xe3500a06
    dcd     0xba000003
    dcd     0xe1a00008
    dcd     0xe3a01024
    bl      func_ov022_020a35f4
    dcd     0xe1a04000
    dcd     0xe1a00004
    dcd     0xe28dd024
    dcd     0xe8bd81f8
    dcd     data_ov090_020bcc00
    dcd     0x00000333
    dcd     data_0203d210
    dcd     0x00001333
}
