extern void VEC_Subtract(void);
extern void func_01ff8d18(void);

asm void func_ov298_020d40e4(void)
{
    dcd     0xe92d000f
    dcd     0xe92d4000
    dcd     0xe24dd00c
    dcd     0xe5901004
    dcd     0xe28d0014
    dcd     0xe5911000
    dcd     0xe28d2000
    dcd     0xe28110b0
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe28dd00c
    dcd     0xe8bd4000
    dcd     0xe28dd010
    dcd     0xe12fff1e
}
