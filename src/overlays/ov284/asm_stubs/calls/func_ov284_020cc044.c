extern void VEC_Subtract(void);
extern void func_01ff8d18(void);

asm void func_ov284_020cc044(void)
{
    dcd     0xe92d4070
    dcd     0xe1a05001
    dcd     0xe3a04000
    dcd     0xe0853104
    dcd     0xe5931398
    dcd     0xe5930388
    dcd     0xe2816058
    dcd     0xe2800014
    dcd     0xe8900007
    dcd     0xe8860007
    dcd     0xe593038c
    dcd     0xe1a01006
    dcd     0xe2800014
    dcd     0xe286200c
    bl      VEC_Subtract
    dcd     0xe286000c
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe2844001
    dcd     0xe5860018
    dcd     0xe3540003
    dcd     0xbaffffec
    dcd     0xe8bd8070
}
