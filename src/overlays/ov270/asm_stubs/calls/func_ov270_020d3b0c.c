extern void func_ov107_020c9ec8(void);
extern void func_ov107_020c6980(void);
extern void func_0203ca9c(void);

asm void func_ov270_020d3b0c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe59503d0
    dcd     0xe1a04001
    bl      func_ov107_020c9ec8
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov107_020c6980
    dcd     0xe5950394
    dcd     0xe285efe9
    dcd     0xe2804004
    dcd     0xe1a0c00e
    dcd     0xe8b4000f
    dcd     0xe8ae000f
    dcd     0xe8b4000f
    dcd     0xe8ae000f
    dcd     0xe8940007
    dcd     0xe88e0007
    dcd     0xe1a0000c
    dcd     0xe59f1004
    bl      func_0203ca9c
    dcd     0xe8bd8038
    dcd     0x000028cc
}
