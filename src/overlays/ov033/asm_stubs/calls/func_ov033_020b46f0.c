extern void func_ov022_02095524(void);
extern void MI_Copy48B(void);
extern void func_0202a818(void);
extern void func_ov033_020b4a34(void);

asm void func_ov033_020b46f0(void)
{
    dcd     0xe92d40f8
    dcd     0xe1a04001
    dcd     0xe5941000
    dcd     0xe1a05000
    dcd     0xe3510002
    dcd     0x1a00000c
    dcd     0xe5951464
    dcd     0xe5950468
    dcd     0xe2011801
    dcd     0xe2000000
    dcd     0xe3500000
    dcd     0x03510000
    dcd     0x1a000005
    dcd     0xe2850fbe
    dcd     0xe2800a02
    bl      func_ov022_02095524
    dcd     0xe3500000
    dcd     0x03a00000
    dcd     0x05840000
    dcd     0xe5940000
    dcd     0xe3500001
    dcd     0x1a00000a
    dcd     0xe2850f56
    dcd     0xe2800b01
    dcd     0xe284108c
    bl      MI_Copy48B
    dcd     0xe2850c2a
    dcd     0xe1d01bfa
    dcd     0xe284000c
    bl      func_0202a818
    dcd     0xe3500000
    dcd     0x13a00002
    dcd     0x15840000
    dcd     0xe2847f46
    dcd     0xe3a06000
    dcd     0xe2854c2a
    dcd     0xe1d41bfa
    dcd     0xe1a00007
    bl      func_ov033_020b4a34
    dcd     0xe2866001
    dcd     0xe3560006
    dcd     0xe2877e11
    dcd     0xbafffff8
    dcd     0xe8bd80f8
}
