extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void VEC_Add(void);
extern void VEC_Mag(void);
extern char data_0203d210[];
extern char data_ov091_020bc100[];
extern char data_ov091_020bc240[];
extern void func_01ff8d18(void);
extern void func_ov022_02091324(void);

asm void func_ov091_020bb490(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd068
    dcd     0xe59f116c
    dcd     0xe59f216c
    dcd     0xe5911000
    dcd     0xe1a05000
    dcd     0xe28100a4
    dcd     0xe2804b0b
    dcd     0xe28de05c
    dcd     0xe8920007
    dcd     0xe88e0007
    dcd     0xe284cf49
    dcd     0xe28d3050
    dcd     0xe89c0007
    dcd     0xe8830007
    dcd     0xe5950020
    dcd     0xe59f213c
    dcd     0xe1d018b0
    dcd     0xe28d002c
    dcd     0xe2411902
    dcd     0xe1a01801
    dcd     0xe1a01821
    dcd     0xe1a01241
    dcd     0xe1a03081
    dcd     0xe2831001
    dcd     0xe1a03083
    dcd     0xe1a01081
    dcd     0xe19230f3
    dcd     0xe19220f1
    dcd     0xe2631000
    dcd     0xe2622000
    bl      MTX_RotY33_
    dcd     0xe59d1058
    dcd     0xe28d0050
    dcd     0xe281109a
    dcd     0xe2811c09
    dcd     0xe58d1058
    dcd     0xe28d102c
    dcd     0xe28d2000
    bl      MTX_MultVec33
    dcd     0xe28d0000
    dcd     0xe285108c
    dcd     0xe2811b01
    dcd     0xe1a02000
    bl      VEC_Add
    dcd     0xe28d005c
    dcd     0xe28d102c
    dcd     0xe1a02000
    bl      MTX_MultVec33
    dcd     0xe28d005c
    bl      VEC_Mag
    dcd     0xe3500000
    dcd     0x0a000002
    dcd     0xe28d005c
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe59de05c
    dcd     0xe3a01000
    dcd     0xe59dc060
    dcd     0xe59d3064
    dcd     0xe3a02001
    dcd     0xe3a00007
    dcd     0xe1cde0bc
    dcd     0xe1cdc0be
    dcd     0xe1cd31b0
    dcd     0xe58d2014
    dcd     0xe58d101c
    dcd     0xe58d1020
    dcd     0xe58d0018
    dcd     0xe58d1024
    dcd     0xe58d1028
    dcd     0xe5940008
    dcd     0xe3500002
    dcd     0x0a000003
    dcd     0xe3a00a02
    dcd     0xe58d1024
    dcd     0xe1cd01b2
    dcd     0xea000003
    dcd     0xe3a01002
    dcd     0xe3a00d96
    dcd     0xe58d1024
    dcd     0xe1cd01b2
    dcd     0xe28d1000
    dcd     0xe1a00005
    bl      func_ov022_02091324
    dcd     0xe5950000
    dcd     0xe3100801
    dcd     0x128dd068
    dcd     0x18bd8038
    dcd     0xe3a00003
    dcd     0xe5c5047a
    mov r0, #1
    dcd     0xe5c5047b
    dcd     0xe28dd068
    dcd     0xe8bd8038
    dcd     data_ov091_020bc240
    dcd     data_ov091_020bc100
    dcd     data_0203d210
}
