extern void func_ov298_020d404c(void);
extern void func_ov107_020c9264(void);
extern void func_02023e80(void);
extern void func_0203c634(void);
extern void func_ov298_020d4834(void);

asm void func_ov298_020d47c0(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    bl      func_ov298_020d404c
    dcd     0xe5940000
    dcd     0xe3a01001
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe3a00c09
    dcd     0xe5840050
    mov r0, #0
    dcd     0xe584008c
    dcd     0xe5942030
    dcd     0xe5941028
    dcd     0xe59f002c
    dcd     0xe0821001
    dcd     0xe5841030
    dcd     0xe5841034
    dcd     0xe5840054
    bl      func_02023e80
    dcd     0xe2800eff
    dcd     0xe584005c
    dcd     0xe1d512d0
    dcd     0xe59f200c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     0x00001fe0
    dcd     func_ov298_020d4834
}
