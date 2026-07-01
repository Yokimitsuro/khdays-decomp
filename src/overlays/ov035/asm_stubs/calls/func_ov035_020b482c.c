extern void FX_Atan2(void);
extern void VEC_Add(void);
extern void VEC_Mag(void);
extern void VEC_Subtract(void);
extern char data_ov035_020b4ca0[];
extern void func_01ff8d18(void);
extern void func_01fff774(void);
extern void func_0202af1c(void);
extern void func_02030788(void);
extern void func_ov022_0209fe20(void);
extern void func_ov022_020a35f4(void);
extern void func_ov022_020ad0c0(void);
extern void func_ov022_020ad114(void);
extern void func_ov035_020b3d44(void);
extern void func_ov035_020b3ef0(void);

asm void func_ov035_020b482c(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd024
    dcd     0xe59f1308
    dcd     0xe1a06000
    dcd     0xe5910000
    dcd     0xe3a05000
    dcd     0xe28000a4
    dcd     0xe2804b0b
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe2860064
    dcd     0xe5962464
    dcd     0xe5901404
    dcd     0xe3822801
    dcd     0xe5862464
    dcd     0xe3811000
    dcd     0xe5801404
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe286006c
    dcd     0xe596246c
    dcd     0xe5901404
    dcd     0xe3822801
    dcd     0xe586246c
    dcd     0xe3811000
    dcd     0xe5801404
    dcd     0xe1d400dc
    dcd     0xe3500000
    dcd     0x1a000022
    dcd     0xe1a00006
    bl      func_ov022_020ad114
    dcd     0xe3500000
    dcd     0x0a00001e
    dcd     0xe1a00006
    bl      func_ov022_020ad0c0
    dcd     0xe286108c
    dcd     0xe28d2018
    dcd     0xe2811b01
    bl      VEC_Subtract
    dcd     0xe3a01000
    dcd     0xe28d0018
    dcd     0xe58d101c
    bl      VEC_Mag
    dcd     0xe3500000
    dcd     0x0a000002
    dcd     0xe28d0018
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe59d0018
    dcd     0xe59d1020
    dcd     0xe2600000
    dcd     0xe2611000
    bl      FX_Atan2
    dcd     0xe5962020
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
    dcd     0xe28d100c
    dcd     0xe1a00006
    bl      func_ov022_0209fe20
    dcd     0xe59d0010
    dcd     0xe3500000
    dcd     0x15860058
    dcd     0x1a00000a
    dcd     0xe5960024
    dcd     0xe3100004
    dcd     0x1a000007
    dcd     0xe5961000
    dcd     0xe5960004
    dcd     0xe3811000
    dcd     0xe5861000
    dcd     0xe3800901
    dcd     0xe5860004
    mov r0, #0
    dcd     0xe5860058
    dcd     0xe28d000c
    dcd     0xe28d3000
    dcd     0xe8900007
    dcd     0xe8830007
    mov r0, #0
    dcd     0xe2862098
    dcd     0xe58d0004
    dcd     0xe2820b01
    dcd     0xe1a01003
    dcd     0xe2822b01
    bl      VEC_Add
    dcd     0xe59607b0
    dcd     0xe3500a03
    dcd     0x1a000010
    dcd     0xe1d410dc
    dcd     0xe1d400dd
    dcd     0xe1510000
    dcd     0xaa00000c
    dcd     0xe5960020
    dcd     0xe3a01000
    dcd     0xe1a02001
    dcd     0xe2800004
    bl      func_01fff774
    mov r0, #0
    dcd     0xe58607b0
    dcd     0xe5961000
    dcd     0xe5960004
    dcd     0xe3811202
    dcd     0xe5861000
    dcd     0xe3800000
    dcd     0xe5860004
    dcd     0xe59607b0
    dcd     0xe3500000
    dcd     0x1a000009
    dcd     0xe5940000
    dcd     0xe3500000
    dcd     0xe1a00006
    dcd     0x1a000001
    bl      func_ov035_020b3d44
    dcd     0xea000000
    bl      func_ov035_020b3ef0
    dcd     0xe1d400dc
    dcd     0xe2800001
    dcd     0xe5c4000c
    dcd     0xe5961668
    dcd     0xe1a00006
    dcd     0xe12fff31
    dcd     0xe5d61694
    dcd     0xe20000ff
    dcd     0xe1a00f80
    dcd     0xe3c11002
    dcd     0xe1811f20
    dcd     0xe20100ff
    dcd     0xe1a00f00
    dcd     0xe5c61694
    dcd     0xe1b00fa0
    dcd     0x0a000015
    dcd     0xe5961000
    dcd     0xe5960004
    dcd     0xe3811000
    dcd     0xe5861000
    dcd     0xe3800802
    dcd     0xe5860004
    dcd     0xe5961020
    dcd     0xe5910000
    dcd     0xe3100020
    dcd     0x1a000001
    dcd     0xe2810004
    bl      func_0202af1c
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe2860064
    dcd     0xe5962464
    dcd     0xe5901404
    dcd     0xe3822002
    dcd     0xe5862464
    dcd     0xe3811000
    dcd     0xe5801404
    dcd     0xe5d60694
    dcd     0xe1a00f00
    dcd     0xe1b00fa0
    dcd     0x0a00001b
    dcd     0xe3a01000
    dcd     0xe58614a0
    dcd     0xe586149c
    dcd     0xe5861498
    dcd     0xe58616a0
    dcd     0xe586169c
    dcd     0xe5861698
    dcd     0xe5962000
    dcd     0xe5960004
    dcd     0xe3822004
    dcd     0xe5862000
    dcd     0xe3800000
    dcd     0xe5860004
    dcd     0xe5960024
    dcd     0xe3100004
    dcd     0x0a000007
    dcd     0xe5962664
    dcd     0xe1a00006
    dcd     0xe12fff32
    dcd     0xe1a00006
    dcd     0xe3a01000
    bl      func_ov022_020a35f4
    dcd     0xe1a05000
    dcd     0xea000003
    dcd     0xe1a00006
    dcd     0xe3a01002
    bl      func_ov022_020a35f4
    dcd     0xe1a05000
    dcd     0xe1a00005
    dcd     0xe28dd024
    dcd     0xe8bd8078
    dcd     data_ov035_020b4ca0
}
