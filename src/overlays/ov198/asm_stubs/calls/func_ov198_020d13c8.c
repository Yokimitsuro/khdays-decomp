extern void VEC_Subtract(void);
extern void data_02041dc8(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov198_020d065c(void);
extern void func_ov198_020d14a8(void);

asm void func_ov198_020d13c8(void) {

    dcd 0xe92d4030
    dcd 0xe24dd00c
    dcd 0xe1a05000
    dcd 0xe59f00c0
    dcd 0xe5954004
    dcd 0xe28dc000
    dcd 0xe8900007
    dcd 0xe88c0007
    dcd 0xe5940000
    dcd 0xe5900394
    dcd 0xe3500000
    dcd 0x0a000014
    dcd 0xe2800074
    dcd 0xe8900007
    dcd 0xe88c0007
    dcd 0xe5940000
    dcd 0xe59d3004
    dcd 0xe5901398
    dcd 0xe1a0000c
    dcd 0xe5911080
    dcd 0xe1a0200c
    dcd 0xe0831001
    dcd 0xe58d1004
    dcd 0xe5941000
    dcd 0xe2811ff6
    bl VEC_Subtract
    dcd 0xe28d0000
    dcd 0xe1a01000
    bl func_01ff8d18
    dcd 0xe59d0000
    dcd 0xe59d1008
    bl func_020050b4
    dcd 0xe5840038
    dcd 0xe5950000
    dcd 0xe5942040
    dcd 0xe590102c
    dcd 0xe59f0040
    dcd 0xe0821001
    dcd 0xe1510000
    dcd 0xb28dd00c
    dcd 0xe5841040
    dcd 0xb8bd8030
    dcd 0xe5942000
    dcd 0xe59d1004
    dcd 0xe1a00004
    dcd 0xe2822ff6
    bl func_ov198_020d065c
    dcd 0xe1d512d0
    dcd 0xe59f2014
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe28dd00c
    dcd 0xe8bd8030
    dcd data_02041dc8
    dcd 0x00001188
    dcd func_ov198_020d14a8
}
