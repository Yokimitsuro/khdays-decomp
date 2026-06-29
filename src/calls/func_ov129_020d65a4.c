extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov129_020d65fc(void);

asm void func_ov129_020d65a4(void)
{
    dcd     0xe92d4070
    dcd     0xe1a06000
    dcd     0xe5964004
    dcd     0xe3a01002
    dcd     0xe5940000
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe5940000
    dcd     0xe5905224
    dcd     0xe5900228
    dcd     0xe0500005
    dcd     0x42600000
    dcd     0xe2800001
    bl      func_02023eb4
    dcd     0xe0850000
    dcd     0xe5840038
    dcd     0xe1d612d0
    dcd     0xe59f2008
    dcd     0xe1a00006
    bl      func_0203c634
    dcd     0xe8bd8070
    dcd     func_ov129_020d65fc
}
