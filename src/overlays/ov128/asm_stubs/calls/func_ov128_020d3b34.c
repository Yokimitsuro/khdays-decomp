extern void func_ov107_020c08cc(void);
extern void func_ov107_020c7500(void);

asm void func_ov128_020d3b34(void)
{
    dcd     0xe92d4070
    dcd     0xe24dd008
    dcd     0xe1a05001
    dcd     0xe5d51002
    dcd     0xe1a06000
    dcd     0xe1a04002
    dcd     0xe3510005
    dcd     0x1a000010
    dcd     0xe5d52003
    dcd     0xe3520000
    dcd     0x1a00000d
    dcd     0xe3a00a02
    dcd     0xe58d0000
    dcd     0xe2850005
    dcd     0xe58d0004
    dcd     0xe5961394
    dcd     0xe596003c
    dcd     0xe7911182
    dcd     0xe3a02017
    dcd     0xe3a03002
    bl      func_ov107_020c08cc
    dcd     0xe5d51003
    dcd     0xe5962394
    dcd     0xe0821181
    dcd     0xe5810004
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov107_020c7500
    dcd     0xe28dd008
    dcd     0xe8bd8070
}
