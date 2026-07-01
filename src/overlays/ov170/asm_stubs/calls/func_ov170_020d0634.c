extern void FX_Inv(void);
extern void FX_Inv_0x01ff8a40(void);
extern void OS_IsThreadAvailable_0x020c9848(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020cab14(void);
extern void func_ov170_020d086c(void);

asm void func_ov170_020d0634(void)
{
    dcd     0xe92d4ff0
    dcd     0xe24dd00c
    dcd     0xe1a0b000
    dcd     0xe59b8004
    dcd     0xe3a01000
    dcd     0xe5980000
    bl      func_ov107_020cab14
    dcd     0xe3500000
    dcd     0x0a000050
    dcd     0xe3a01000
    dcd     0xe5881038
    dcd     0xe5881030
    dcd     0xe5981008
    dcd     0xe28d2000
    dcd     0xe2800074
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe59f31d0
    dcd     0xe1a01fa0
    dcd     0xe0c42093
    dcd     0xe0804004
    dcd     0xe0814544
    dcd     0xe59f01c0
    dcd     0xe28d1000
    dcd     0xe5884034
    dcd     0xe288200c
    bl      func_01ffa724
    dcd     0xe5980010
    dcd     0xe3a0a000
    dcd     0xe5880040
    dcd     0xe588a03c
    dcd     0xe5980034
    dcd     0xe1a0900a
    dcd     0xe0800fa0
    dcd     0xe1a000c0
    dcd     0xe3500000
    dcd     0xda000017
    dcd     0xe3e05000
    dcd     0xe24540ff
    dcd     0xe1a0700a
    dcd     0xe3a06b02
    bl      OS_IsThreadAvailable_0x020c9848
    dcd     0xe5900040
    bl      FX_Inv_0x01ff8a40
    dcd     0xe0812490
    dcd     0xe0922006
    dcd     0xe0211590
    dcd     0xe1a00fc0
    dcd     0xe0211490
    dcd     0xe0a10007
    dcd     0xe1a01622
    dcd     0xe1811a00
    dcd     0xe598003c
    dcd     0xe0899001
    dcd     0xe0400009
    dcd     0xe588003c
    dcd     0xe5980034
    dcd     0xe28aa001
    dcd     0xe0800fa0
    dcd     0xe15a00c0
    dcd     0xbaffffeb
    dcd     0xe5980034
    dcd     0xe1b00600
    dcd     0xe5880034
    dcd     0x0a00000a
    dcd     0xe3500a0f
    dcd     0xaa000008
    dcd     0xe3a01a0f
    bl      FX_Inv
    dcd     0xe288100c
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe5981010
    dcd     0xe3a00a0f
    dcd     0xe5881040
    dcd     0xe5880034
    dcd     0xe5980000
    dcd     0xe2883018
    dcd     0xe2800e39
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe59f00d8
    bl      func_02023eb4
    dcd     0xe3e01f59
    dcd     0xe598201c
    dcd     0xe0800001
    dcd     0xe0820000
    dcd     0xe588001c
    dcd     0xe5980000
    dcd     0xe5983008
    dcd     0xe59f10b8
    dcd     0xe3a02005
    bl      func_ov107_020c5af8
    dcd     0xe5980000
    dcd     0xe2884024
    dcd     0xe1d026b0
    dcd     0xe3a03000
    dcd     0xe1a01802
    dcd     0xe1a01c21
    dcd     0xe3c11080
    dcd     0xe1a01801
    dcd     0xe1a01821
    dcd     0xe3c22cff
    dcd     0xe1a01c01
    dcd     0xe1821821
    dcd     0xe1c016b0
    dcd     0xe5982000
    dcd     0xe1d216b0
    dcd     0xe1a00801
    dcd     0xe1a00c20
    dcd     0xe3800001
    dcd     0xe3c11cff
    dcd     0xe1a00c00
    dcd     0xe1810820
    dcd     0xe1c206b0
    dcd     0xe5980000
    dcd     0xe5902388
    dcd     0xe5921008
    dcd     0xe1a00c01
    dcd     0xe1a00c20
    dcd     0xe3800001
    dcd     0xe3c110ff
    dcd     0xe20000ff
    dcd     0xe1810000
    dcd     0xe5820008
    dcd     0xe5980008
    dcd     0xe8900007
    dcd     0xe8840007
    dcd     0xe5c83048
    dcd     0xe1db12d0
    dcd     0xe59f201c
    dcd     0xe1a0000b
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd8ff0
    dcd     0xa00a00a1
    dcd     0x00000666
    dcd     0x000002cb
    dcd     0x0000013f
    dcd     func_ov170_020d086c
}
