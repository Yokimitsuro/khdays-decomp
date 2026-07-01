extern void func_ov107_020cab14(void);
extern void FX_Sqrt(void);
extern void func_0203c634(void);
extern void data_ov293_020d3660(void);

asm void func_ov293_020d273c(void)
{
    dcd     0xe92d40f8
    dcd     0xe1a05000
    dcd     0xe5951000
    dcd     0xe3a0001e
    dcd     0xe591102c
    dcd     0xe59f20c8
    dcd     0xe0030091
    dcd     0xe1a00fa3
    dcd     0xe0c31392
    dcd     0xe5954004
    dcd     0xe08030c3
    dcd     0xe5843014
    dcd     0xe5940000
    dcd     0xe28d1000
    bl      func_ov107_020cab14
    dcd     0xe1b07000
    dcd     0xe5840004
    dcd     0x08bd80f8
    dcd     0xe5946000
    dcd     0xe59d0000
    bl      FX_Sqrt
    dcd     0xe59f108c
    dcd     0xe5973080
    dcd     0xe5962080
    dcd     0xe5911008
    dcd     0xe0832002
    dcd     0xe0400002
    dcd     0xe58d0000
    dcd     0xe3510000
    dcd     0x1a000010
    dcd     0xe5950000
    dcd     0xe5941040
    dcd     0xe590002c
    dcd     0xe0811000
    dcd     0xe5841040
    dcd     0xe5940018
    dcd     0xe1510000
    dcd     0xb8bd80f8
    dcd     0xe3a02000
    dcd     0xe5842040
    dcd     0xe5940000
    dcd     0xe3a01004
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd80f8
    dcd     0xe3500a03
    dcd     0xb8bd80f8
    dcd     0xe5940000
    dcd     0xe3a01004
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd80f8
    dcd     0x66666667
    dcd     data_ov293_020d3660
}
