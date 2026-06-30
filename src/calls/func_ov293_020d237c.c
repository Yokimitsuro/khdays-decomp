extern void OS_IsThreadAvailable_0x020c9848(void);
extern void func_0203d040(void);
extern void func_0202f188(void);
extern void func_0203c9d0(void);
extern void data_ov293_020d3660(void);
extern void data_02042264(void);
extern void data_02041dc8(void);

asm void func_ov293_020d237c(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd010
    dcd     0xe59f10b4
    dcd     0xe1a05000
    dcd     0xe5910008
    dcd     0xe5954004
    dcd     0xe3500000
    dcd     0x0a000011
    bl      OS_IsThreadAvailable_0x020c9848
    dcd     0xe59f1098
    dcd     0xe5900044
    dcd     0xe5911004
    dcd     0xe1510000
    dcd     0x0a00000b
    bl      OS_IsThreadAvailable_0x020c9848
    dcd     0xe5901044
    dcd     0xe59f007c
    dcd     0xe5801004
    dcd     0xe5951000
    dcd     0xe5902000
    dcd     0xe591102c
    dcd     0xe0821001
    dcd     0xe5801000
    dcd     0xe3510a02
    dcd     0xc3a01000
    dcd     0xc5801008
    dcd     0xe594000c
    dcd     0xe5941010
    dcd     0xe5942014
    dcd     0xe3a03000
    bl      func_0203d040
    dcd     0xe59f1044
    dcd     0xe584000c
    dcd     0xe1a02000
    dcd     0xe28d0000
    bl      func_0202f188
    dcd     0xe5940000
    dcd     0xe28d1000
    dcd     0xe28000a0
    bl      func_0203c9d0
    dcd     0xe494001c
    dcd     0xe28030f0
    dcd     0xe8940007
    dcd     0xe8830007
    dcd     0xe59f0014
    dcd     0xe8900007
    dcd     0xe8840007
    dcd     0xe28dd010
    dcd     0xe8bd8038
    dcd     data_ov293_020d3660
    dcd     data_02042264
    dcd     data_02041dc8
}
