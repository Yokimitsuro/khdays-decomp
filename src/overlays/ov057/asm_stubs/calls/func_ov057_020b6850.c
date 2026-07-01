extern void func_0202a818(void);
extern void func_ov057_020b6af4(void);
extern void data_ov057_020b74a0(void);

asm void func_ov057_020b6850(void)
{
    dcd     0xe92d4070
    dcd     0xe59f3088
    dcd     0xe1a04001
    dcd     0xe5931000
    dcd     0xe5943000
    dcd     0xe281102c
    dcd     0xe1a05000
    dcd     0xe3530001
    dcd     0xe2816b0b
    dcd     0x1a000004
    dcd     0xe59506bc
    dcd     0xe350002f
    dcd     0x13500032
    dcd     0x13a00000
    dcd     0x15840000
    dcd     0xe5940000
    dcd     0xe3500001
    dcd     0x0a000002
    dcd     0xe3500002
    dcd     0x0a000005
    dcd     0xe8bd8070
    dcd     0xe59507b0
    dcd     0xe3500a12
    dcd     0xa3a00002
    dcd     0xa5840000
    dcd     0xe8bd8070
    dcd     0xe1a01002
    dcd     0xe2840004
    bl      func_0202a818
    dcd     0xe3500000
    dcd     0x08bd8070
    dcd     0xe1a00005
    dcd     0xe2861f46
    bl      func_ov057_020b6af4
    mov r0, #0
    dcd     0xe5840000
    dcd     0xe8bd8070
    dcd     data_ov057_020b74a0
}
