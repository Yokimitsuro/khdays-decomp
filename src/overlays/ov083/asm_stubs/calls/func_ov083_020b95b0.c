extern char data_ov083_020b9b00[];
extern void func_01ffd0e8(void);
extern void func_0202c2f8(void);

asm void func_ov083_020b95b0(void)
{
    dcd     0xe92d4010
    dcd     0xe24dd018
    dcd     0xe28dc00c
    dcd     0xe1a04001
    dcd     0xe8900007
    dcd     0xe88c0007
    dcd     0xe89c0007
    dcd     0xe8840007
    dcd     0xe3a03000
    dcd     0xe59f0068
    dcd     0xe59f2068
    dcd     0xe5901000
    dcd     0xe58d2004
    dcd     0xe58d3000
    dcd     0xe58d3008
    dcd     0xe1d106b6
    dcd     0xe5913020
    dcd     0xe28d2000
    dcd     0xe1a0100c
    bl      func_0202c2f8
    dcd     0xe3500000
    dcd     0x05940004
    dcd     0x028dd018
    dcd     0x02800a05
    dcd     0x05840004
    dcd     0x08bd8010
    dcd     0xe590000c
    dcd     0xe28d1000
    dcd     0xe28d200c
    dcd     0xe1a03004
    bl      func_01ffd0e8
    dcd     0xe5940004
    dcd     0xe2400067
    dcd     0xe2400c0e
    dcd     0xe5840004
    dcd     0xe28dd018
    dcd     0xe8bd8010
    dcd     data_ov083_020b9b00
    dcd     0x00005ccd
}
