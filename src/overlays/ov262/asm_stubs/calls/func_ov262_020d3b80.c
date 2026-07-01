extern void func_ov107_020c6980(void);
extern void func_ov002_02076ce8(void);

asm void func_ov262_020d3b80(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    bl      func_ov107_020c6980
    dcd     0xe5940398
    dcd     0xe284e0a0
    dcd     0xe280c010
    dcd     0xe8be000f
    dcd     0xe8ac000f
    dcd     0xe8be000f
    dcd     0xe8ac000f
    dcd     0xe89e0007
    dcd     0xe88c0007
    dcd     0xe59403a0
    dcd     0xe5900000
    dcd     0xe3500000
    dcd     0x08bd8010
    dcd     0xe5941398
    dcd     0xe2811020
    bl      func_ov002_02076ce8
    dcd     0xe8bd8010
}
