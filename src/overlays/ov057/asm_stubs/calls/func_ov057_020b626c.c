extern void func_ov057_020b6960(void);
extern void func_ov057_020b6588(void);
extern void func_ov057_020b6c30(void);
extern void func_ov057_020b67cc(void);
extern void func_ov057_020b68e8(void);

asm void func_ov057_020b626c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5d52694
    dcd     0xe1a04001
    dcd     0xe1a01f82
    dcd     0xe1b01fa1
    dcd     0x08bd8038
    dcd     0xe2841f8a
    bl      func_ov057_020b6960
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov057_020b6588
    dcd     0xe1a00005
    dcd     0xe2841f46
    bl      func_ov057_020b6c30
    dcd     0xe1a00005
    dcd     0xe2841fce
    bl      func_ov057_020b67cc
    dcd     0xe2841044
    dcd     0xe1a00005
    dcd     0xe2811b01
    bl      func_ov057_020b68e8
    dcd     0xe8bd8038
}
