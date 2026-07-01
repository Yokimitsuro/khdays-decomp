extern void OS_IsThreadAvailable_0x020c9848(void);
extern void VEC_Add(void);
extern void func_01ffa724(void);
extern void func_02016320(void);
extern void func_0203c960(void);
extern void func_0203ca30(void);
extern void func_0203ca9c(void);

asm void func_ov214_020cbfc8(void) {

    dcd 0xe92d4010
    dcd 0xe24dd048
    dcd 0xe1a04001
    dcd 0xe5900088
    dcd 0xe5943438
    dcd 0xe28d1018
    dcd 0xe2800020
    dcd 0xe3a02000
    bl func_02016320
    dcd 0xe3500000
    dcd 0x0a00001f
    dcd 0xe28d003c
    dcd 0xe28d300c
    dcd 0xe8900007
    dcd 0xe8830007
    dcd 0xe2840ffd
    bl func_0203c960
    bl OS_IsThreadAvailable_0x020c9848
    dcd 0xe5901000
    dcd 0xe3a00b05
    dcd 0xe28d2000
    dcd 0xe2600000
    dcd 0xe281107c
    bl func_01ffa724
    dcd 0xe28d000c
    dcd 0xe28d1000
    dcd 0xe1a02000
    bl VEC_Add
    dcd 0xe2840ffd
    dcd 0xe28d100c
    bl func_0203ca30
    dcd 0xe2840ffd
    dcd 0xe3a01a01
    bl func_0203ca9c
    dcd 0xe59403ac
    dcd 0xe28d103c
    dcd 0xe5900000
    dcd 0xe2800010
    bl func_0203ca30
    dcd 0xe59403b0
    dcd 0xe28d103c
    dcd 0xe2800010
    bl func_0203ca30
    dcd 0xe284c0a0
    dcd 0xe2844ff2
    dcd 0xe8bc000f
    dcd 0xe8a4000f
    dcd 0xe8bc000f
    dcd 0xe8a4000f
    dcd 0xe89c0007
    dcd 0xe8840007
    dcd 0xe28dd048
    dcd 0xe8bd8010
}
