extern void func_02033e48(void);
extern void data_ov077_020b9b80(void);

asm void func_ov077_020b89e4(void)
{
    dcd     0xe92d4010
    dcd     0xe59f002c
    dcd     0xe3a02000
    dcd     0xe5900000
    dcd     0xe280002c
    dcd     0xe5812000
    dcd     0xe2804b0b
    dcd     0xe5940550
    dcd     0xe3500000
    dcd     0x08bd8010
    bl      func_02033e48
    dcd     0xe3a00000
    dcd     0xe5840550
    dcd     0xe8bd8010
    dcd     data_ov077_020b9b80
}
