extern void VEC_Subtract(void);
extern void func_01ff8a14(void);
extern void func_020050b4(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020cab14(void);
extern void func_ov157_020ce7e4(void);
extern void func_ov157_020ce8c8(void);
extern void func_ov157_020cf9f4(void);

asm void func_ov157_020cf820(void)
{
    dcd     0xe92d4070
    dcd     0xe24dd018
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe5840018
    dcd     0xe3500000
    dcd     0x0a000010
    dcd     0xe5941008
    dcd     0xe28d200c
    dcd     0xe2800e19
    bl      VEC_Subtract
    dcd     0xe59d000c
    dcd     0xe59d1014
    bl      func_020050b4
    dcd     0xe5840014
    dcd     0xe5951000
    dcd     0xe3a0001e
    dcd     0xe591202c
    dcd     0xe59f1164
    dcd     0xe0030092
    dcd     0xe0c20391
    dcd     0xe1a00fa3
    dcd     0xe0802142
    dcd     0xe5842030
    dcd     0xe5950000
    dcd     0xe594102c
    dcd     0xe590002c
    dcd     0xe0810000
    dcd     0xe584002c
    dcd     0xe5d40038
    dcd     0xe3500000
    dcd     0x1a000008
    dcd     0xe594102c
    dcd     0xe59f012c
    dcd     0xe1510000
    dcd     0xba000004
    dcd     0xe1a00004
    dcd     0xe2841020
    bl      func_ov157_020ce7e4
    mov r0, #1
    dcd     0xe5c40038
    dcd     0xe594202c
    dcd     0xe59f1108
    dcd     0xe1520001
    dcd     0xba00000c
    dcd     0xe59f0100
    dcd     0xe1520000
    dcd     0xca000009
    dcd     0xe2610000
    dcd     0xe0820000
    dcd     0xe1a01121
    bl      func_01ff8a14
    dcd     0xe1a03000
    dcd     0xe1a02001
    dcd     0xe1a00004
    dcd     0xe1a01003
    dcd     0xe2843020
    bl      func_ov157_020ce8c8
    dcd     0xe5940004
    dcd     0xe5d00000
    dcd     0xe3500000
    dcd     0x128dd018
    dcd     0x18bd8070
    dcd     0xe5941000
    dcd     0xe3a00003
    dcd     0xe591338c
    dcd     0xe5932008
    dcd     0xe1a01c02
    dcd     0xe1a01c21
    dcd     0xe3c11001
    dcd     0xe3c220ff
    dcd     0xe20110ff
    dcd     0xe1821001
    dcd     0xe5831008
    bl      func_02023eb4
    dcd     0xe2800001
    dcd     0xe584001c
    dcd     0xe5940000
    dcd     0xe3a01005
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe5940018
    dcd     0xe3500000
    dcd     0x0a00000c
    dcd     0xe5941008
    dcd     0xe28d2000
    dcd     0xe2800e19
    bl      VEC_Subtract
    dcd     0xe59f0058
    bl      func_02023eb4
    dcd     0xe3e01ec9
    dcd     0xe0806001
    dcd     0xe59d0000
    dcd     0xe59d1008
    bl      func_020050b4
    dcd     0xe0800006
    dcd     0xe5840014
    mov r0, #0
    dcd     0xe584002c
    dcd     0xe5c40038
    dcd     0xe5d41039
    dcd     0xe59f2028
    dcd     0xe1a00005
    dcd     0xe3c11002
    dcd     0xe5c41039
    dcd     0xe1d512d0
    bl      func_0203c634
    dcd     0xe28dd018
    dcd     0xe8bd8070
    dcd     0x66666667
    dcd     0x00001bbb
    dcd     0x000022a9
    dcd     0x00001923
    dcd     func_ov157_020cf9f4
}
