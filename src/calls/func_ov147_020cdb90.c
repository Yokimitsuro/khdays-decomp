extern void VEC_Subtract(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov147_020cc9c0(void);
extern void func_ov147_020ccb30(void);
extern void func_ov147_020cdc18(void);

asm void func_ov147_020cdb90(void) {

    dcd 0xe92d4038
    dcd 0xe24dd010
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe28d2004
    dcd 0xe5940000
    dcd 0xe594100c
    dcd 0xe2800e19
    bl VEC_Subtract
    dcd 0xe3a00000
    dcd 0xe58d0000
    dcd 0xe28d1004
    dcd 0xe1a00004
    dcd 0xe891000e
    bl func_ov147_020ccb30
    dcd 0xe5940004
    dcd 0xe5d000ad
    dcd 0xe3500000
    dcd 0x128dd010
    dcd 0x18bd8038
    dcd 0xe5940000
    dcd 0xe3a01003
    dcd 0xe3a02001
    bl func_ov107_020c9264
    dcd 0xe5940000
    dcd 0xe3a01001
    bl func_ov147_020cc9c0
    dcd 0xe1d512d0
    dcd 0xe59f200c
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe28dd010
    dcd 0xe8bd8038
    dcd func_ov147_020cdc18
}
