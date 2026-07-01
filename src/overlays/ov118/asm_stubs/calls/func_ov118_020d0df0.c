extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_0203c634(void);
extern void func_ov107_020cab14(void);
extern void func_ov118_020d0200(void);
extern void func_ov118_020d0f34(void);

asm void func_ov118_020d0df0(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd00c
    dcd     0xe1a06000
    dcd     0xe5964004
    dcd     0xe3a01000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe5840004
    dcd     0xe3500000
    dcd     0x1a000008
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d612d0
    dcd     0xe1a00006
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd8078
    dcd     0xe5941000
    dcd     0xe28d2000
    dcd     0xe2800e19
    dcd     0xe28110b0
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe1a05000
    dcd     0xe3550902
    dcd     0xe1a00004
    dcd     0xe2841018
    dcd     0xc3a05902
    bl      func_ov118_020d0200
    dcd     0xe3a00c02
    dcd     0xe2600000
    dcd     0xe5840030
    dcd     0xe5940000
    dcd     0xe5d0017a
    dcd     0xe1a00f80
    dcd     0xe1b00fa0
    dcd     0x028dd00c
    dcd     0x08bd8078
    dcd     0xe59d2008
    dcd     0xe59d1000
    dcd     0xe3a00000
    dcd     0xe5841064
    dcd     0xe5840068
    dcd     0xe2840064
    dcd     0xe1a01000
    dcd     0xe584206c
    bl      func_01ff8d18
    dcd     0xe59f3068
    dcd     0xe1a01fa5
    dcd     0xe0c02593
    dcd     0xe0850000
    dcd     0xe0810240
    dcd     0xe2841064
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe3a00000
    dcd     0xe5840060
    dcd     0xe5940044
    dcd     0xe59f2040
    dcd     0xe5901004
    dcd     0xe1a00006
    dcd     0xe5841070
    dcd     0xe5944000
    dcd     0xe1d436b0
    dcd     0xe1a01803
    dcd     0xe1a01c21
    dcd     0xe3811002
    dcd     0xe3c33cff
    dcd     0xe1a01c01
    dcd     0xe1831821
    dcd     0xe1c416b0
    dcd     0xe1d612d0
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd8078
    dcd     0x88888889
    dcd     func_ov118_020d0f34
}
