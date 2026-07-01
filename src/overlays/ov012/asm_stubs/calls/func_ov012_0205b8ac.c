extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_02020a78(void);

asm void func_ov012_0205b8ac(void)
{
    dcd     0xe92d4008
    bl      NNSi_FndGetCurrentRootHeap
    dcd     0xe1d010b2
    dcd     0xe3811008
    dcd     0xe1c010b2
    dcd     0xe3110010
    dcd     0x03a00000
    dcd     0x08bd8008
    dcd     0xe3a00005
    dcd     0xe3a01e19
    bl      func_02020a78
    dcd     0xe3e00001
    dcd     0xe8bd8008
}
