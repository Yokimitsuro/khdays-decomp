extern void NNSi_FndDestroyDoubleList(void);
extern void func_0203c7e8(void);
extern void func_ov107_020c68ec(void);

asm void func_ov287_020cfdf8(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5950384
    bl      func_0203c7e8
    dcd     0xe3a04000
    dcd     0xe0850184
    dcd     0xe59003c0
    dcd     0xe3500000
    dcd     0x0a000000
    bl      func_0203c7e8
    dcd     0xe2844001
    dcd     0xe3540002
    dcd     0xbafffff7
    dcd     0xe2850fe6
    bl      NNSi_FndDestroyDoubleList
    dcd     0xe1a00005
    bl      func_ov107_020c68ec
    dcd     0xe8bd8038
}
