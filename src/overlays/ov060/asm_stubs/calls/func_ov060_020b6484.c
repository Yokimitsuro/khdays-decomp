extern void func_01fff774(void);
extern void func_0202a818(void);
extern void func_0202accc(void);
extern void func_ov022_020a4490(void);

asm void func_ov060_020b6484(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe59506bc
    dcd     0xe1a04001
    dcd     0xe350002f
    dcd     0x15940000
    dcd     0x13500000
    dcd     0x13a00000
    dcd     0x15840000
    dcd     0xe5940000
    dcd     0xe3500001
    dcd     0x0a000002
    dcd     0xe3500002
    dcd     0x0a000022
    dcd     0xe8bd8038
    dcd     0xe59506bc
    dcd     0xe350002f
    dcd     0x1a00001b
    dcd     0xe59507b0
    dcd     0xe3500a03
    dcd     0xb8bd8038
    dcd     0xe3a01000
    dcd     0xe1a03001
    dcd     0xe2840004
    dcd     0xe28420e4
    bl      func_0202accc
    dcd     0xe2840004
    dcd     0xe28420e4
    dcd     0xe3a01002
    dcd     0xe3a03000
    bl      func_0202accc
    dcd     0xe3a01000
    dcd     0xe1a02001
    dcd     0xe2840004
    bl      func_01fff774
    dcd     0xe2840004
    dcd     0xe3a01002
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe3a01002
    dcd     0xe5841000
    dcd     0xe1a00005
    dcd     0xe3a010d7
    dcd     0xe3a02000
    bl      func_ov022_020a4490
    dcd     0xe8bd8038
    mov r0, #0
    dcd     0xe5840000
    dcd     0xe8bd8038
    dcd     0xe1a01002
    dcd     0xe2840004
    bl      func_0202a818
    dcd     0xe3500000
    dcd     0x13a00001
    dcd     0x15840000
    dcd     0x18bd8038
    dcd     0xe59506bc
    dcd     0xe350002f
    dcd     0x18bd8038
    dcd     0xe59507b0
    dcd     0xe3500a03
    dcd     0xb3a00001
    dcd     0xb5840000
    dcd     0xe8bd8038
}
