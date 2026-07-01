extern void func_ov038_020b4160(void);
extern void func_ov038_020b3d88(void);
extern void func_ov038_020b4430(void);
extern void func_ov038_020b3fcc(void);
extern void func_ov038_020b40e8(void);

asm void func_ov038_020b3a6c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5d52694
    dcd     0xe1a04001
    dcd     0xe1a01f82
    dcd     0xe1b01fa1
    dcd     0x08bd8038
    dcd     0xe2841f8a
    bl      func_ov038_020b4160
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov038_020b3d88
    dcd     0xe1a00005
    dcd     0xe2841f46
    bl      func_ov038_020b4430
    dcd     0xe1a00005
    dcd     0xe2841fce
    bl      func_ov038_020b3fcc
    dcd     0xe2841044
    dcd     0xe1a00005
    dcd     0xe2811b01
    bl      func_ov038_020b40e8
    dcd     0xe8bd8038
}
