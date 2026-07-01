extern void NNSi_FndAllocFromDefaultExpHeap(void);
extern void func_ov022_020911f0(void);
extern void func_ov022_02091298(void);
extern void data_ov078_020ba4bc(void);
extern void func_ov078_020b9360(void);
extern void func_ov078_020b94a0(void);

asm void func_ov078_020b91b4(void)
{
    dcd     0xe92d40f8
    dcd     0xe24dd0a8
    dcd     0xe1a04000
    dcd     0xe3a00030
    bl      NNSi_FndAllocFromDefaultExpHeap
    dcd     0xe2842a02
    dcd     0xe3a01000
    dcd     0xe5820644
    dcd     0xe1a02001
    bl      func_ov022_020911f0
    dcd     0xe3a07000
    dcd     0xe3a02c01
    dcd     0xe59f00e4
    dcd     0xe59fc0e4
    dcd     0xe3a0ea01
    dcd     0xe3a060cd
    dcd     0xe3a03003
    dcd     0xe3a01c03
    dcd     0xe3a05005
    dcd     0xe58d0008
    dcd     0xe3a00006
    dcd     0xe58de018
    dcd     0xe58dc048
    dcd     0xe28de008
    dcd     0xe28dc058
    dcd     0xe1cd65b0
    dcd     0xe58d700c
    dcd     0xe1cd71b2
    dcd     0xe58d7014
    dcd     0xe58d701c
    dcd     0xe58d7020
    dcd     0xe58d7024
    dcd     0xe58d7028
    dcd     0xe58d7030
    dcd     0xe1cd35b2
    dcd     0xe58d2034
    dcd     0xe58d1038
    dcd     0xe58d203c
    dcd     0xe58d5040
    dcd     0xe5cd0054
    dcd     0xe8be000f
    dcd     0xe8ac000f
    dcd     0xe2555001
    dcd     0x1afffffb
    dcd     0xe59d1058
    dcd     0xe59d0090
    dcd     0xe3812c02
    dcd     0xe3800020
    dcd     0xe3a01a02
    dcd     0xe58d2058
    dcd     0xe58d1098
    dcd     0xe58d0090
    dcd     0xe3a00002
    dcd     0xe58d0000
    dcd     0xe3a00006
    dcd     0xe58d0004
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
    dcd     0xe8bd80f8
    dcd     0x000005c9
    dcd     0x00001333
    dcd     data_ov078_020ba4bc
    dcd     func_ov078_020b9360
    dcd     func_ov078_020b94a0
}
