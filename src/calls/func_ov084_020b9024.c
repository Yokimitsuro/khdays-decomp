extern void func_ov084_020b91c8(void);
extern void func_ov084_020b93c8(void);

asm void func_ov084_020b9024(void)
{
    dcd     0xe92d4038
    dcd     0xe5d02694
    dcd     0xe1a04001
    dcd     0xe1a02f82
    dcd     0xe1b02fa2
    dcd     0x08bd8038
    bl      func_ov084_020b91c8
    dcd     0xe2845f4a
    dcd     0xe3a04000
    dcd     0xe1a00005
    bl      func_ov084_020b93c8
    dcd     0xe2844001
    dcd     0xe3540006
    dcd     0xe2855e12
    dcd     0xbafffff9
    dcd     0xe8bd8038
}
