extern void func_02023eb4(void);
extern void func_02023e80(void);
extern void func_ov298_020d404c(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020c5af8(void);
extern void func_0203c634(void);
extern void func_ov298_020d51fc(void);

asm void func_ov298_020d510c(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd00c
    dcd     0xe1a05000
    dcd     0xe3a00064
    dcd     0xe5954004
    bl      func_02023eb4
    dcd     0xe3500032
    dcd     0x2a000016
    dcd     0xe59f00c0
    bl      func_02023e80
    dcd     0xe2800022
    dcd     0xe2801c19
    dcd     0xe1a00005
    dcd     0xe5841028
    bl      func_ov298_020d404c
    dcd     0xe5941000
    dcd     0xe28d2000
    dcd     0xe5910394
    dcd     0xe2811074
    dcd     0xe2800074
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe59d0000
    dcd     0xe59d1008
    bl      func_020050b4
    dcd     0xe5840030
    dcd     0xe5941028
    dcd     0xe0800001
    dcd     0xe5840030
    dcd     0xe5940000
    dcd     0xe3a01008
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    mov r0, #1
    dcd     0xe5840090
    dcd     0xe5940000
    dcd     0xe3a01000
    dcd     0xe590c38c
    dcd     0xe3a02043
    dcd     0xe59c3008
    dcd     0xe1a00c03
    dcd     0xe1a00c20
    dcd     0xe3800001
    dcd     0xe3c330ff
    dcd     0xe20000ff
    dcd     0xe1830000
    dcd     0xe58c0008
    dcd     0xe5940000
    dcd     0xe5943008
    bl      func_ov107_020c5af8
    dcd     0xe1d512d0
    dcd     0xe59f2010
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd8030
    dcd     0x00001922
    dcd     func_ov298_020d51fc
}
