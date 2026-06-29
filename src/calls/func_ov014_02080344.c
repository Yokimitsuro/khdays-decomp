extern void func_01ff8e94(void);
extern void func_01fffde0(void);
extern void func_01fffe14(void);
extern void func_ov002_0207285c(void);

asm void func_ov014_02080344(void)
{
    dcd     0xe92d40f0
    dcd     0xe24dd00c
    dcd     0xe1a07000
    dcd     0xe5975008
    bl      func_01fffe14
    bl      func_01fffde0
    dcd     0xe1b04000
    dcd     0x028dd00c
    dcd     0x03a00000
    dcd     0x08bd80f0
    dcd     0xe1d466f6
    dcd     0xe5d70010
    bl      func_ov002_0207285c
    dcd     0xe1560000
    dcd     0x128dd00c
    dcd     0x13a00000
    dcd     0x18bd80f0
    dcd     0xe284008c
    dcd     0xe2800b01
    dcd     0xe28d3000
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe1a01003
    dcd     0xe287001c
    bl      func_01ff8e94
    dcd     0xe595106c
    dcd     0xe1510000
    dcd     0xa3a00001
    dcd     0xb3a00000
    dcd     0xe28dd00c
    dcd     0xe8bd80f0
}
