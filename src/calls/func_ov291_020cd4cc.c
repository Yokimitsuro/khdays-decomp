extern void func_02020400(void);
extern void func_0203c634(void);

asm void func_ov291_020cd4cc(void)
{
    dcd     0xe92d4038
    dcd     0xe1a04000
    dcd     0xe5945004
    dcd     0xe5950020
    dcd     0xe5d00000
    dcd     0xe3500000
    dcd     0x18bd8038
    dcd     0xe5950000
    dcd     0xe5952024
    dcd     0xe59013a0
    dcd     0xe2820001
    dcd     0xe5911008
    bl      func_02020400
    dcd     0xe5851024
    dcd     0xe5950000
    dcd     0xe3a01003
    dcd     0xe5c011c7
    dcd     0xe1d412d0
    dcd     0xe1a00004
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd8038
}
