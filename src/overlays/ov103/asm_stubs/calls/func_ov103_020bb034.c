extern void func_ov103_020bb180(void);
extern void func_ov103_020bb390(void);
extern void func_ov103_020bb56c(void);

asm void func_ov103_020bb034(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5d52694
    dcd     0xe1a04001
    dcd     0xe1a02f82
    dcd     0xe1b02fa2
    dcd     0x08bd8038
    bl      func_ov103_020bb180
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov103_020bb390
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov103_020bb56c
    dcd     0xe8bd8038
}
