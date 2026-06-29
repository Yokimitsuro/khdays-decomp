extern char data_ov104_020bc24c[];
extern void NNSi_FndAllocFromDefaultExpHeap(void);
extern void func_ov022_020911f0(void);
extern void func_ov022_02091298(void);
extern void func_ov104_020bb948(void);

asm void func_ov104_020bb4f4(void)
{
    dcd     0xe92d40f8
    dcd     0xe24dd0a8
    dcd     0xe1a04000
    dcd     0xe3a00030
    bl      NNSi_FndAllocFromDefaultExpHeap
    dcd     0xe2841a02
    dcd     0xe5810644
    dcd     0xe3a01000
    dcd     0xe3a02001
    bl      func_ov022_020911f0
    dcd     0xe3a07000
    dcd     0xe3a02c01
    dcd     0xe59f00cc
    dcd     0xe59fc0cc
    dcd     0xe3a0e001
    dcd     0xe3a06a0a
    dcd     0xe3a03903
    dcd     0xe3a01c03
    dcd     0xe3a05005
    dcd     0xe58d0008
    dcd     0xe3a0000a
    dcd     0xe58de00c
    dcd     0xe58dc014
    dcd     0xe28de008
    dcd     0xe28dc058
    dcd     0xe58d601c
    dcd     0xe1cd71b2
    dcd     0xe58d7018
    dcd     0xe58d3020
    dcd     0xe58d7024
    dcd     0xe58d7028
    dcd     0xe58d7030
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
    dcd     0xe59f2058
    dcd     0xe3811c02
    dcd     0xe3800020
    dcd     0xe58d2064
    dcd     0xe58d1058
    dcd     0xe58d0090
    dcd     0xe3a00002
    dcd     0xe58d0000
    dcd     0xe3a0000a
    dcd     0xe58d0004
    dcd     0xe2840a02
    dcd     0xe5900644
    dcd     0xe59f202c
    dcd     0xe28d3008
    dcd     0xe1a01004
    bl      func_ov022_02091298
    dcd     0xe2840a02
    dcd     0xe5900644
    dcd     0xe59f1018
    dcd     0xe5801020
    dcd     0xe28dd0a8
    dcd     0xe8bd80f8
    dcd     0x000001c1
    dcd     0x00000ccd
    dcd     0x00001333
    dcd     data_ov104_020bc24c
    dcd     func_ov104_020bb948
}
