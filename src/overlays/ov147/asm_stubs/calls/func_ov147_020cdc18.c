extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_0203c634(void);
extern void func_ov147_020ccb30(void);

asm void func_ov147_020cdc18(void) {

    dcd 0xe92d4070
    dcd 0xe24dd010
    dcd 0xe1a04000
    dcd 0xe5945004
    dcd 0xe28d2004
    dcd 0xe5950000
    dcd 0xe595100c
    dcd 0xe2800e19
    bl VEC_Subtract
    mov r0, #0
    dcd 0xe58d0000
    dcd 0xe28d1004
    dcd 0xe1a00005
    dcd 0xe891000e
    bl func_ov147_020ccb30
    dcd 0xe28d0004
    dcd 0xe5956000
    dcd 0xe1a01000
    bl func_01ff8d18
    dcd 0xe5961080
    dcd 0xe0400001
    dcd 0xe3500a02
    dcd 0xa28dd010
    dcd 0xa8bd8070
    dcd 0xe5950000
    dcd 0xe3a01002
    dcd 0xe5c011c7
    dcd 0xe1d412d0
    dcd 0xe1a00004
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd010
    dcd 0xe8bd8070
}
