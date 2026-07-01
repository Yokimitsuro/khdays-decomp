extern void OS_IsThreadAvailable_0x020c9848(void);
extern void VEC_Add(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_0203ca30(void);
extern void func_ov107_020c4924(void);

asm void func_ov163_020ce0a0(void) {

    dcd 0xe92d4010
    dcd 0xe24dd018
    dcd 0xe1a04000
    bl func_ov107_020c4924
    dcd 0xe59403c0
    dcd 0xe284cfe5
    dcd 0xe280e004
    dcd 0xe8be000f
    dcd 0xe8ac000f
    dcd 0xe8be000f
    dcd 0xe8ac000f
    dcd 0xe89e0007
    dcd 0xe88c0007
    bl OS_IsThreadAvailable_0x020c9848
    dcd 0xe5900000
    dcd 0xe2841fe9
    dcd 0xe2800088
    dcd 0xe28d2000
    bl VEC_Subtract
    dcd 0xe28d0000
    dcd 0xe1a01000
    bl func_01ff8d18
    dcd 0xe3a00b02
    dcd 0xe28d1000
    dcd 0xe28d200c
    bl func_01ffa724
    dcd 0xe28d100c
    dcd 0xe2840fe9
    dcd 0xe1a02001
    bl VEC_Add
    dcd 0xe2840fe5
    dcd 0xe28d100c
    bl func_0203ca30
    dcd 0xe28dd018
    dcd 0xe8bd8010
}
