extern void func_02033e48(void);
extern void data_ov057_020b74a0(void);

asm void func_ov057_020b6304(void)
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
    mov r0, #0
    dcd     0xe5840550
    dcd     0xe8bd8010
    dcd     data_ov057_020b74a0
}
