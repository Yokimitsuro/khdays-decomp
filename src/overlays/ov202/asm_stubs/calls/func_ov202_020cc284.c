extern void OS_IsThreadAvailable_0x020c9848(void);
extern void VEC_Add(void);
extern void func_01ffa724(void);
extern void func_0203ca30(void);
extern void func_ov107_020c4924(void);

asm void func_ov202_020cc284(void) {

    dcd 0xe92d4018
    dcd 0xe24dd00c
    dcd 0xe1a04000
    bl func_ov107_020c4924
    dcd 0xe59403d4
    dcd 0xe284cff9
    dcd 0xe280e004
    dcd 0xe8be000f
    dcd 0xe8ac000f
    dcd 0xe8be000f
    dcd 0xe8ac000f
    dcd 0xe89e0007
    dcd 0xe88c0007
    bl OS_IsThreadAvailable_0x020c9848
    dcd 0xe5901000
    dcd 0xe3a00b01
    dcd 0xe281107c
    dcd 0xe2600000
    dcd 0xe28d2000
    bl func_01ffa724
    dcd 0xe28d1000
    dcd 0xe2840ffd
    dcd 0xe1a02001
    bl VEC_Add
    dcd 0xe2840ff9
    dcd 0xe28d1000
    bl func_0203ca30
    dcd 0xe28dd00c
    dcd 0xe8bd8018
}
