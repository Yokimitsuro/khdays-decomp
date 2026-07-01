extern void NNSi_FndDestroyDoubleList(void);
extern void func_01fffc24(void);
extern void func_01fffca8(void);

asm void func_ov128_020d3bb0(void)
{
    dcd     0xe92d43f8
    dcd     0xe1a09000
    dcd     0xe2890fe6
    dcd     0xe1a08001
    dcd     0xe1a07002
    bl      NNSi_FndDestroyDoubleList
    dcd     0xe2890fe6
    bl      func_01fffc24
    dcd     0xe1a08128
    dcd     0xe3a06000
    dcd     0xe3580000
    dcd     0xd8bd83f8
    dcd     0xe3a05004
    dcd     0xe3a04064
    dcd     0xe1a01005
    dcd     0xe1a02004
    dcd     0xe2890fe6
    bl      func_01fffca8
    dcd     0xe4971004
    dcd     0xe2866001
    dcd     0xe5801000
    dcd     0xe1560008
    dcd     0xbafffff6
    dcd     0xe8bd83f8
}
