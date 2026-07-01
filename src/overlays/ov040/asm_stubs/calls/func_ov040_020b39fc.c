extern void func_ov040_020b3b58(void);
extern void func_ov040_020b3ca0(void);
extern void func_ov040_020b3fc0(void);

asm void func_ov040_020b39fc(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5d52694
    dcd     0xe1a04001
    dcd     0xe1a01f82
    dcd     0xe1b01fa1
    dcd     0x08bd8038
    dcd     0xe2841008
    bl      func_ov040_020b3b58
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov040_020b3ca0
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov040_020b3fc0
    dcd     0xe8bd8038
}
