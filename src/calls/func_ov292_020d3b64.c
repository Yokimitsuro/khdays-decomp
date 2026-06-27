extern void func_01fffc24(void);
extern void NNSi_FndDestroyDoubleList(void);
extern void func_01fffca8(void);

asm void func_ov292_020d3b64(void)
{
    dcd     0xe92d43f8
    dcd     0xe1a06000
    dcd     0xe2860fe5
    dcd     0xe1a05001
    dcd     0xe1a04002
    bl      NNSi_FndDestroyDoubleList
    dcd     0xe2860fe5
    bl      func_01fffc24
    dcd     0xe59f004c
    dcd     0xe1a01005
    dcd     0xe0850091
    dcd     0xe1a051a5
    dcd     0xe3a09000
    dcd     0xe3550000
    dcd     0xd8bd83f8
    dcd     0xe3a0800c
    dcd     0xe3a07064
    dcd     0xe1a01008
    dcd     0xe1a02007
    dcd     0xe2860fe5
    bl      func_01fffca8
    dcd     0xe1a03000
    dcd     0xe8940007
    dcd     0xe2899001
    dcd     0xe8830007
    dcd     0xe1590005
    dcd     0xe284400c
    dcd     0xbafffff4
    dcd     0xe8bd83f8
    dcd     0xaaaaaaab
}
