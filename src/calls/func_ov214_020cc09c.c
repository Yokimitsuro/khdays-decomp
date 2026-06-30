extern void VEC_Mag(void);
extern void VEC_Subtract(void);
extern void data_02041dc8(void);
extern void func_02016320(void);
extern void func_0203b9fc(void);
extern void func_0203bc78(void);

asm void func_ov214_020cc09c(void) {

    dcd 0xe92d4030
    dcd 0xe24dd054
    dcd 0xe1a05000
    dcd 0xe5954084
    bl func_0203bc78
    dcd 0xe5950088
    dcd 0xe5943434
    dcd 0xe28d1024
    dcd 0xe2800020
    dcd 0xe3a02000
    bl func_02016320
    dcd 0xe3500000
    dcd 0x0a000010
    dcd 0xe28d0048
    dcd 0xe28d3018
    dcd 0xe8900007
    dcd 0xe8830007
    dcd 0xe2842024
    dcd 0xe1a00003
    dcd 0xe2841fed
    dcd 0xe2822b01
    bl VEC_Subtract
    dcd 0xe28d0018
    dcd 0xe284cfed
    dcd 0xe8900007
    dcd 0xe2843024
    dcd 0xe88c0007
    dcd 0xe2830b01
    bl VEC_Mag
    dcd 0xe5840430
    dcd 0xe5d500ad
    dcd 0xe3500000
    dcd 0x128dd054
    dcd 0x18bd8030
    dcd 0xe5950088
    dcd 0xe1d020f2
    dcd 0xe3520001
    dcd 0x13520002
    dcd 0x0a000002
    dcd 0xe3520003
    dcd 0x0a000009
    dcd 0xea000017
    dcd 0xe2820001
    dcd 0xe1a02800
    dcd 0xe3a01000
    dcd 0xe1a00005
    dcd 0xe1a03001
    dcd 0xe1a02842
    bl func_0203b9fc
    dcd 0xe28dd054
    dcd 0xe8bd8030
    dcd 0xe3a01000
    dcd 0xe28d500c
    dcd 0xe59f0080
    dcd 0xe5841430
    dcd 0xe2843024
    dcd 0xe8900007
    dcd 0xe8850007
    dcd 0xe2844fed
    dcd 0xe8950007
    dcd 0xe8840007
    dcd 0xe2833b01
    dcd 0xe8950007
    dcd 0xe8830007
    dcd 0xe28dd054
    dcd 0xe8bd8030
    dcd 0xe3520000
    dcd 0xba000003
    dcd 0xe3a01000
    dcd 0xe1a00005
    dcd 0xe1a03001
    bl func_0203b9fc
    dcd 0xe3a01000
    dcd 0xe59f0030
    dcd 0xe5841430
    dcd 0xe28d5000
    dcd 0xe2843024
    dcd 0xe8900007
    dcd 0xe8850007
    dcd 0xe2844fed
    dcd 0xe8950007
    dcd 0xe8840007
    dcd 0xe2833b01
    dcd 0xe8950007
    dcd 0xe8830007
    dcd 0xe28dd054
    dcd 0xe8bd8030
    dcd data_02041dc8
}
