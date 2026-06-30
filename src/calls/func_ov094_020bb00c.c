extern void func_ov094_020bb700(void);
extern void func_ov094_020bb328(void);
extern void func_ov094_020bb9d0(void);
extern void func_ov094_020bb56c(void);
extern void func_ov094_020bb688(void);

asm void func_ov094_020bb00c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5d52694
    dcd     0xe1a04001
    dcd     0xe1a01f82
    dcd     0xe1b01fa1
    dcd     0x08bd8038
    dcd     0xe2841f8a
    bl      func_ov094_020bb700
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov094_020bb328
    dcd     0xe1a00005
    dcd     0xe2841f46
    bl      func_ov094_020bb9d0
    dcd     0xe1a00005
    dcd     0xe2841fce
    bl      func_ov094_020bb56c
    dcd     0xe2841044
    dcd     0xe1a00005
    dcd     0xe2811b01
    bl      func_ov094_020bb688
    dcd     0xe8bd8038
}
