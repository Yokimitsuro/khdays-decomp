extern void NNSi_FndAllocFromDefaultExpHeap(void);
extern void func_ov022_020911f0(void);
extern void func_ov022_02091298(void);
extern char data_ov045_020b4c08[];
extern void func_ov045_020b4968(void);
extern void func_ov045_020b4900(void);

asm void func_ov045_020b476c(void)
{
    dcd     0xe92d4010
    dcd     0xe24dd0a8
    dcd     0xe1a04000
    dcd     0xe3a00030
    bl      NNSi_FndAllocFromDefaultExpHeap
    dcd     0xe2841a02
    dcd     0xe5810644
    dcd     0xe3a01000
    dcd     0xe3a02002
    bl      func_ov022_020911f0
    dcd     0xe59f0104
    dcd     0xe3a02005
    dcd     0xe58d0048
    dcd     0xe3a0c000
    dcd     0xe3a03c01
    dcd     0xe3a0100a
    dcd     0xe2600a02
    dcd     0xe58d0064
    dcd     0xe3a00a0a
    dcd     0xe58d001c
    dcd     0xe58d006c
    dcd     0xe3a00a12
    dcd     0xe58d0020
    dcd     0xe58d0070
    dcd     0xe3a00c03
    dcd     0xe58d0038
    dcd     0xe58d0088
    dcd     0xe2820ff7
    dcd     0xe58d0058
    dcd     0xe59f00bc
    dcd     0xe58d2040
    dcd     0xe58d0008
    dcd     0xe3a00b02
    dcd     0xe58d0014
    dcd     0xe3a00a02
    dcd     0xe58d0098
    dcd     0xe3a00003
    dcd     0xe3a02002
    dcd     0xe58d0094
    dcd     0xe3a00025
    dcd     0xe58d0090
    dcd     0xe58dc00c
    dcd     0xe1cdc1b2
    dcd     0xe58dc018
    dcd     0xe58dc024
    dcd     0xe58dc028
    dcd     0xe58dc030
    dcd     0xe58d3034
    dcd     0xe58d303c
    dcd     0xe5cd1054
    dcd     0xe58d2044
    dcd     0xe58dc05c
    dcd     0xe1cdc6b2
    dcd     0xe58dc068
    dcd     0xe58dc074
    dcd     0xe58dc078
    dcd     0xe58dc080
    dcd     0xe58d3084
    dcd     0xe58d308c
    dcd     0xe5cd10a4
    dcd     0xe58d2000
    dcd     0xe58d1004
    dcd     0xe2840a02
    dcd     0xe5900644
    dcd     0xe59f2034
    dcd     0xe28d3008
    dcd     0xe1a01004
    bl      func_ov022_02091298
    dcd     0xe2840a02
    dcd     0xe5902644
    dcd     0xe59f3020
    dcd     0xe59f1020
    dcd     0xe5823020
    dcd     0xe5900644
    dcd     0xe5801024
    dcd     0xe28dd0a8
    dcd     0xe8bd8010
    dcd     0x00001333
    dcd     0x000001e1
    dcd     data_ov045_020b4c08
    dcd     func_ov045_020b4968
    dcd     func_ov045_020b4900
}
