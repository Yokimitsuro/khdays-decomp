extern void func_ov239_020cc9f0(void);
extern void func_ov239_020cdb2c(void);

asm void func_ov239_020cdb08(void)
{
    dcd     0xe92d4008
    dcd     0xe59fc014
    dcd     0xe3a01002
    dcd     0xe3a02000
    dcd     0xe3a03001
    dcd     0xe58dc000
    bl      func_ov239_020cc9f0
    dcd     0xe8bd8008
    dcd     func_ov239_020cdb2c
}
