extern void VEC_Add(void);
extern void func_0203c634(void);
extern void func_ov107_020c0b90(void);
extern void func_ov107_020c5af8(void);
extern void func_ov276_020d13b8(void);

asm void func_ov276_020d1334(void) {

    dcd 0xe92d4030
    dcd 0xe24dd014
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe28d2008
    dcd 0xe5940000
    dcd 0xe5901470
    dcd 0xe2800074
    dcd 0xe2800b01
    dcd 0xe281102c
    bl VEC_Add
    dcd 0xe3a01001
    dcd 0xe28d0008
    dcd 0xe58d1004
    dcd 0xe24d3008
    dcd 0xe8900007
    dcd 0xe8830007
    dcd 0xe5940000
    dcd 0xe3a01000
    dcd 0xe893000c
    bl func_ov107_020c0b90
    dcd 0xe5940000
    dcd 0xe3a01000
    dcd 0xe3a02048
    dcd 0xe28d3008
    bl func_ov107_020c5af8
    dcd 0xe1d512d0
    dcd 0xe59f200c
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe28dd014
    dcd 0xe8bd8030
    dcd func_ov276_020d13b8
}
