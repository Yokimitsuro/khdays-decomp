extern char data_0203d210[];
extern char data_02042258[];
extern void VEC_Add(void);
extern void VEC_DotProduct(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_01fffd70(void);
extern void func_01fffd8c(void);
extern void func_ov243_020d3c94(void);

asm void func_ov243_020d3d78(void)
{
    dcd     0xe92d4ff8
    dcd     0xe24dd040
    dcd     0xe5906004
    dcd     0xe59f11d4
    dcd     0xe5960000
    dcd     0xe59f21d0
    dcd     0xe59043b0
    dcd     0xe5909004
    dcd     0xe0857194
    dcd     0xe0255294
    dcd     0xe1a02fc4
    dcd     0xe0255192
    dcd     0xe2971000
    dcd     0xe3a0b000
    dcd     0xe2a51b02
    dcd     0xe1a01201
    dcd     0xe1a01821
    dcd     0xe1a01241
    dcd     0xe1a04081
    dcd     0xe2841001
    dcd     0xe1a00081
    dcd     0xe59f2194
    dcd     0xe1a04084
    dcd     0xe19240f4
    dcd     0xe19200f0
    dcd     0xe3a03b02
    dcd     0xe28d1034
    dcd     0xe58d003c
    dcd     0xe28d2028
    dcd     0xe58d4034
    dcd     0xe58db038
    dcd     0xe2430a02
    dcd     0xe24b7106
    bl      func_01ffa724
    dcd     0xe5961000
    dcd     0xe28d0028
    dcd     0xe2811074
    dcd     0xe1a02000
    bl      VEC_Add
    dcd     0xe28900a8
    bl      func_01fffd70
    dcd     0xe3500000
    dcd     0x01a0a00b
    dcd     0x1590a000
    dcd     0xe35a0000
    dcd     0x0a000048
    dcd     0xe59f0134
    dcd     0xe28d3004
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe28d5010
    dcd     0xe28d401c
    dcd     0xe59a0040
    dcd     0xe1a00f00
    dcd     0xe1b00fc0
    dcd     0x0a000037
    dcd     0xe1da06b0
    dcd     0xe1a00c00
    dcd     0xe1a00c20
    dcd     0xe3100001
    dcd     0x0a000032
    dcd     0xe28a0074
    dcd     0xe8900007
    dcd     0xe8850007
    dcd     0xe5961000
    dcd     0xe1a00005
    dcd     0xe1a02004
    dcd     0xe2811074
    bl      VEC_Subtract
    dcd     0xe59d0020
    dcd     0xe3500000
    dcd     0xb2600000
    dcd     0xe3500a1e
    dcd     0xca000025
    dcd     0xe3a01000
    dcd     0xe58d1020
    dcd     0xe1a00004
    dcd     0xe1a01004
    bl      func_01ff8d18
    dcd     0xe1a08000
    dcd     0xe1580007
    dcd     0xaa00001d
    dcd     0xe1a00005
    dcd     0xe28d1028
    dcd     0xe1a02004
    bl      VEC_Subtract
    dcd     0xe3a00000
    dcd     0xe58d0020
    dcd     0xe1a00004
    dcd     0xe1a01004
    bl      func_01ff8d18
    dcd     0xe3500000
    dcd     0x028d0004
    dcd     0x08900007
    dcd     0x08840007
    dcd     0xe3580b06
    dcd     0xda000006
    dcd     0xe3580902
    dcd     0xca00000c
    dcd     0xe1a00004
    dcd     0xe28d1034
    bl      VEC_DotProduct
    dcd     0xe3500eb5
    dcd     0xba000007
    dcd     0xe59a1080
    dcd     0xe1a00006
    dcd     0xe58d1000
    dcd     0xe895000e
    bl      func_ov243_020d3c94
    dcd     0xe3500000
    dcd     0x11a07008
    dcd     0x11a0b00a
    dcd     0xe28900a8
    bl      func_01fffd8c
    dcd     0xe3500000
    dcd     0x03a0a000
    dcd     0x1590a000
    dcd     0xe35a0000
    dcd     0x1affffbc
    dcd     0xe1a0000b
    dcd     0xe28dd040
    dcd     0xe8bd8ff8
    dcd     0x60db9391
    dcd     0x000028be
    dcd     data_0203d210
    dcd     data_02042258
}
