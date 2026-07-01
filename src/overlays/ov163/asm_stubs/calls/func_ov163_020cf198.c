extern void VEC_DotProduct(void);
extern void VEC_Subtract(void);
extern void data_0203d210(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020cab14(void);
extern void func_ov163_020cf340(void);

asm void func_ov163_020cf198(void) {

    dcd 0xe92d40f8
    dcd 0xe24dd018
    dcd 0xe1a06000
    dcd 0xe5964004
    dcd 0xe3a01000
    dcd 0xe5940000
    bl func_ov107_020cab14
    dcd 0xe5840008
    dcd 0xe3500000
    dcd 0x1a000008
    dcd 0xe5940000
    dcd 0xe3a01002
    dcd 0xe5c011c7
    dcd 0xe1d612d0
    dcd 0xe1a00006
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd018
    dcd 0xe8bd80f8
    dcd 0xe5941000
    dcd 0xe28d200c
    dcd 0xe2800e19
    dcd 0xe28110b0
    bl VEC_Subtract
    dcd 0xe3a00000
    dcd 0xe58d0010
    dcd 0xe28d000c
    dcd 0xe5945000
    dcd 0xe5947008
    dcd 0xe1a01000
    bl func_01ff8d18
    dcd 0xe5973080
    dcd 0xe5952080
    dcd 0xe59d1014
    dcd 0xe0832002
    dcd 0xe0405002
    dcd 0xe59d000c
    bl func_020050b4
    dcd 0xe5840010
    dcd 0xe594300c
    dcd 0xe59f00f0
    dcd 0xe59f10f0
    dcd 0xe08c2093
    dcd 0xe02cc193
    dcd 0xe1a01fc3
    dcd 0xe2922000
    dcd 0xe02cc091
    dcd 0xe2ac0b02
    dcd 0xe1a00200
    dcd 0xe1a00820
    dcd 0xe3a02000
    dcd 0xe1a00240
    dcd 0xe58d2004
    dcd 0xe1a01080
    dcd 0xe2810001
    dcd 0xe59f20bc
    dcd 0xe1a01081
    dcd 0xe19210f1
    dcd 0xe1a00080
    dcd 0xe19220f0
    dcd 0xe58d1000
    dcd 0xe28d0000
    dcd 0xe28d100c
    dcd 0xe58d2008
    bl VEC_DotProduct
    dcd 0xe3500000
    dcd 0xb2600000
    dcd 0xe3a01c03
    dcd 0xe0823190
    dcd 0xe1a00fc0
    dcd 0xe0222190
    dcd 0xe2933b02
    dcd 0xe2a22000
    dcd 0xe1a00623
    dcd 0xe1800a02
    dcd 0xe28d1000
    dcd 0xe2842018
    bl func_01ffa724
    dcd 0xe5940000
    dcd 0xe59012d8
    dcd 0xe1550001
    dcd 0xba000007
    dcd 0xe3a01002
    dcd 0xe5c011c7
    dcd 0xe1d612d0
    dcd 0xe1a00006
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd018
    dcd 0xe8bd80f8
    dcd 0xe3550a01
    dcd 0xc28dd018
    dcd 0xc8bd80f8
    dcd 0xe3a01009
    dcd 0xe3a02000
    bl func_ov107_020c9264
    dcd 0xe1d612d0
    dcd 0xe59f2018
    dcd 0xe1a00006
    bl func_0203c634
    dcd 0xe28dd018
    dcd 0xe8bd80f8
    dcd 0x60db9391
    dcd 0x000028be
    dcd data_0203d210
    dcd func_ov163_020cf340
}
