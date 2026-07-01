extern void data_02041dc8(void);
extern void func_01ffa724(void);
extern void func_0203c634(void);
extern void func_ov107_020c0b90(void);
extern void func_ov107_020c9264(void);
extern void func_ov220_020d3704(void);

asm void func_ov220_020d3614(void) {

    dcd 0xe92d4038
    dcd 0xe24dd008
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe284c030
    dcd 0xe2843024
    dcd 0xe89c0007
    dcd 0xe8830007
    dcd 0xe1a0100c
    dcd 0xe1a0200c
    dcd 0xe3a00c0b
    bl func_01ffa724
    dcd 0xe594001c
    dcd 0xe3500002
    dcd 0xa28dd008
    dcd 0xa8bd8038
    dcd 0xe5950000
    dcd 0xe5941014
    dcd 0xe590002c
    dcd 0xe0510000
    dcd 0xe5840014
    dcd 0x43a00000
    dcd 0x45840014
    dcd 0xe5d4003e
    dcd 0xe3500000
    dcd 0x05940014
    dcd 0x03500000
    dcd 0x1a000004
    dcd 0xe5940004
    dcd 0xe3a01000
    dcd 0xe5c010a8
    mov r0, #1
    dcd 0xe5c4003e
    dcd 0xe5940004
    dcd 0xe5d000ad
    dcd 0xe3500000
    dcd 0x128dd008
    dcd 0x18bd8038
    dcd 0xe5940000
    dcd 0xe3a01009
    dcd 0xe3a02000
    bl func_ov107_020c9264
    dcd 0xe3a01002
    dcd 0xe59f0034
    dcd 0xe58d1004
    dcd 0xe24d3008
    dcd 0xe8900007
    dcd 0xe8830007
    dcd 0xe5940000
    dcd 0xe3a01004
    dcd 0xe893000c
    bl func_ov107_020c0b90
    dcd 0xe1d512d0
    dcd 0xe59f2010
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe28dd008
    dcd 0xe8bd8038
    dcd data_02041dc8
    dcd func_ov220_020d3704
}
