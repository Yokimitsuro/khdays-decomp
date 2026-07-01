extern void func_ov107_020c2b20(void);
extern void func_ov107_020c7b70(void);

asm void func_ov123_020cc33c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe1a04001
    dcd     0xe5951394
    dcd     0xe1a00004
    bl      func_ov107_020c2b20
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov107_020c7b70
    dcd     0xe8bd8038
}
