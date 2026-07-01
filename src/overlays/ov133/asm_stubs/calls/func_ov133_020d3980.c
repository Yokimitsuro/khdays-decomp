extern void data_02041dc8(void);
extern void data_ov133_020d49cc(void);
extern void func_02031384(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov133_020d3a54(void);

asm void func_ov133_020d3980(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe5940048
    dcd     0xe5d00000
    dcd     0xe3500000
    dcd     0x18bd8038
    dcd     0xe59f10a4
    dcd     0xe3a00004
    dcd     0xe1d120b6
    dcd     0xe1d130b4
    dcd     0xe28d1000
    dcd     0xe1cd20b2
    dcd     0xe1cd30b0
    dcd     0xe5943000
    dcd     0xe1a02000
    dcd     0xe1d330b2
    dcd     0xe1cd30b0
    bl      func_02031384
    dcd     0xe5940000
    dcd     0xe3a01007
    dcd     0xe3a02001
    bl      func_ov107_020c9264
    dcd     0xe5942000
    dcd     0xe59f0064
    dcd     0xe59213cc
    dcd     0xe2843024
    dcd     0xe3c11001
    dcd     0xe58213cc
    dcd     0xe8900007
    dcd     0xe8830007
    mov r0, #0
    dcd     0xe5840058
    dcd     0xe5840030
    dcd     0xe5944000
    dcd     0xe59f203c
    dcd     0xe1d416b0
    dcd     0xe1a00005
    dcd     0xe3c13cff
    dcd     0xe1a01801
    dcd     0xe1a01c21
    dcd     0xe3c11040
    dcd     0xe1a01801
    dcd     0xe1a01821
    dcd     0xe1a01c01
    dcd     0xe1831821
    dcd     0xe1c416b0
    dcd     0xe1d512d0
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     data_ov133_020d49cc
    dcd     data_02041dc8
    dcd     func_ov133_020d3a54
}
