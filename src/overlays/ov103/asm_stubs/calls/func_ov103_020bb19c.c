extern void func_01fff774(void);
extern void func_0202accc(void);
extern void func_ov022_020a4490(void);

asm void func_ov103_020bb19c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a04001
    dcd     0xe5941000
    dcd     0xe3a02000
    dcd     0xe3510000
    dcd     0xe1a05002
    dcd     0x13a02001
    dcd     0xe3a010d5
    dcd     0x13a05002
    bl      func_ov022_020a4490
    dcd     0xe5840370
    dcd     0xe1a01805
    dcd     0xe1a03841
    dcd     0xe5942114
    dcd     0xe284000c
    dcd     0xe3a01000
    bl      func_0202accc
    dcd     0xe1a01805
    dcd     0xe1a03841
    dcd     0xe5942114
    dcd     0xe284000c
    dcd     0xe3a01002
    bl      func_0202accc
    dcd     0xe1a00805
    dcd     0xe1a03840
    dcd     0xe5942114
    dcd     0xe284000c
    dcd     0xe3a01001
    bl      func_0202accc
    dcd     0xe3a01000
    dcd     0xe284000c
    dcd     0xe1a02001
    bl      func_01fff774
    dcd     0xe284000c
    dcd     0xe3a01002
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe284000c
    dcd     0xe3a01001
    dcd     0xe3a02000
    bl      func_01fff774
    mov r0, #1
    dcd     0xe5840008
    mov r0, #0
    dcd     0xe5840118
    dcd     0xe8bd8038
}
