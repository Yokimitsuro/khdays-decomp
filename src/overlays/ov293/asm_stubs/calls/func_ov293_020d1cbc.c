extern void func_ov107_020c9ec8(void);
extern void func_ov107_020c6980(void);

asm void func_ov293_020d1cbc(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe595039c
    dcd     0xe1a04001
    bl      func_ov107_020c9ec8
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov107_020c6980
    dcd     0xe8bd8038
}
