extern void func_ov041_020b3d84(void);
extern void func_ov041_020b40dc(void);
extern void func_ov041_020b4224(void);
extern void func_ov041_020b439c(void);

asm void func_ov041_020b3c10(void)
{
    dcd     0xe92d40f8
    dcd     0xe1a07000
    dcd     0xe5d72694
    dcd     0xe1a06001
    dcd     0xe1a02f82
    dcd     0xe1b02fa2
    dcd     0x08bd80f8
    bl      func_ov041_020b3d84
    dcd     0xe2865e33
    dcd     0xe3a04000
    dcd     0xe1a00007
    dcd     0xe1a01005
    bl      func_ov041_020b40dc
    dcd     0xe2844001
    dcd     0xe3540003
    dcd     0xe2855e11
    dcd     0xbafffff8
    dcd     0xe1a00007
    dcd     0xe2861e11
    bl      func_ov041_020b4224
    dcd     0xe1a00007
    dcd     0xe2861e22
    bl      func_ov041_020b439c
    dcd     0xe8bd80f8
}
