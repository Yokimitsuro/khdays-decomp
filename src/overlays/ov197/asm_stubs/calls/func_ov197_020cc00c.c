extern void VEC_Subtract(void);
extern void data_02041dc8(void);
extern void data_02042264(void);
extern void func_01ff8d18(void);
extern void func_02016320(void);
extern void func_0202f188(void);
extern void func_0203b9fc(void);
extern void func_0203bc78(void);

asm void func_ov197_020cc00c(void) {

    dcd 0xe92d4078
    dcd 0xe24dd054
    dcd 0xe1a05000
    dcd 0xe5954084
    bl func_0203bc78
    dcd 0xe5950088
    dcd 0xe59433d0
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
    dcd 0xe59403e4
    dcd 0xe3500000
    dcd 0x1a000003
    dcd 0xe1a00003
    dcd 0xe2841fe9
    dcd 0xe2842e3b
    bl VEC_Subtract
    dcd 0xe28d0018
    dcd 0xe2843fe9
    dcd 0xe8900007
    dcd 0xe8830007
    dcd 0xe3a00000
    dcd 0xe58403e4
    dcd 0xe5d500ad
    dcd 0xe3500000
    dcd 0x128dd054
    dcd 0x18bd8078
    dcd 0xe5950088
    dcd 0xe1d060f2
    dcd 0xe3560000
    dcd 0x13560001
    dcd 0x1a000024
    dcd 0xe59403e8
    dcd 0xe3500000
    dcd 0x0a000021
    dcd 0xe5940394
    dcd 0xe3500000
    dcd 0x0a000012
    dcd 0xe28d200c
    dcd 0xe2800e19
    dcd 0xe28410b0
    bl VEC_Subtract
    dcd 0xe28d000c
    dcd 0xe1a01000
    bl func_01ff8d18
    dcd 0xe3500b12
    dcd 0xe59403bc
    dcd 0xca000004
    dcd 0xe3500000
    dcd 0xc59f0080
    dcd 0xd59f0080
    dcd 0xe58403bc
    dcd 0xea000003
    dcd 0xe3500000
    dcd 0xc59f0074
    dcd 0xd3e00d43
    dcd 0xe58403bc
    dcd 0xe3a01000
    dcd 0xe1a00005
    dcd 0xe1a02006
    dcd 0xe1a03001
    bl func_0203b9fc
    dcd 0xe59413bc
    dcd 0xe3e00000
    dcd 0xe0020091
    dcd 0xe59f104c
    dcd 0xe2840d0f
    dcd 0xe58423bc
    bl func_0202f188
    dcd 0xe59f0040
    dcd 0xe28d5000
    dcd 0xe8900007
    dcd 0xe8850007
    dcd 0xe2843fe9
    dcd 0xe8950007
    dcd 0xe8830007
    dcd 0xe2843e3b
    dcd 0xe8950007
    dcd 0xe8830007
    dcd 0xe3a00001
    dcd 0xe58403e4
    dcd 0xe28dd054
    dcd 0xe8bd8078
    dcd 0x0000244d
    dcd 0xffffdbb3
    dcd 0x000010c1
    dcd data_02042264
    dcd data_02041dc8
}
