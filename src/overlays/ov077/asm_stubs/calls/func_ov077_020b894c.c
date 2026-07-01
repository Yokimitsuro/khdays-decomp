extern void func_ov077_020b9040(void);
extern void func_ov077_020b8c68(void);
extern void func_ov077_020b9310(void);
extern void func_ov077_020b8eac(void);
extern void func_ov077_020b8fc8(void);

asm void func_ov077_020b894c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5d52694
    dcd     0xe1a04001
    dcd     0xe1a01f82
    dcd     0xe1b01fa1
    dcd     0x08bd8038
    dcd     0xe2841f8a
    bl      func_ov077_020b9040
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov077_020b8c68
    dcd     0xe1a00005
    dcd     0xe2841f46
    bl      func_ov077_020b9310
    dcd     0xe1a00005
    dcd     0xe2841fce
    bl      func_ov077_020b8eac
    dcd     0xe2841044
    dcd     0xe1a00005
    dcd     0xe2811b01
    bl      func_ov077_020b8fc8
    dcd     0xe8bd8038
}
