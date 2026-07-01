extern void data_02041dc8(void);
extern void func_01ffa724(void);

asm void func_ov198_020d1ea0(void) {

    dcd 0xe92d4010
    dcd 0xe5904004
    dcd 0xe5940000
    dcd 0xe2800c01
    dcd 0xe1d00cd6
    dcd 0xe3500000
    dcd 0x1a000004
    dcd 0xe59f003c
    dcd 0xe2843008
    dcd 0xe8900007
    dcd 0xe8830007
    dcd 0xea000005
    dcd 0xe3500001
    dcd 0x1a000003
    dcd 0xe2841014
    dcd 0xe2842008
    dcd 0xe3a00b02
    bl func_01ffa724
    dcd 0xe5941000
    dcd 0xe2840008
    dcd 0xe28130f0
    dcd 0xe8900007
    dcd 0xe8830007
    dcd 0xe8bd8010
    dcd data_02041dc8
}
