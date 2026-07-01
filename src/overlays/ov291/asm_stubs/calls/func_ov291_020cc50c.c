extern void func_ov107_020c6980(void);
extern void func_ov107_020c9ec8(void);

asm void func_ov291_020cc50c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5950394
    dcd     0xe1a04001
    bl      func_ov107_020c9ec8
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov107_020c6980
    dcd     0xe8bd8038
}
