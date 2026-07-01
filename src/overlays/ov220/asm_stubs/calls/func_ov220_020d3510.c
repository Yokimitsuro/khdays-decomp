extern void data_02041dc8(void);
extern void func_01ffa724(void);
extern void func_0203c634(void);
extern void func_ov107_020c0b90(void);
extern void func_ov107_020c9264(void);
extern void func_ov220_020d3614(void);

asm void func_ov220_020d3510(void) {

    dcd 0xe92d40f8
    dcd 0xe24dd008
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe2846030
    dcd 0xe2843024
    dcd 0xe8960007
    dcd 0xe8830007
    dcd 0xe1a01006
    dcd 0xe1a02006
    dcd 0xe3a00c0b
    bl func_01ffa724
    dcd 0xe5940004
    dcd 0xe5d000ad
    dcd 0xe3500000
    dcd 0x128dd008
    dcd 0x18bd80f8
    dcd 0xe5940000
    dcd 0xe3a01008
    dcd 0xe3a02001
    bl func_ov107_020c9264
    dcd 0xe3a01000
    dcd 0xe59f009c
    dcd 0xe58d1004
    dcd 0xe24d3008
    dcd 0xe8900007
    dcd 0xe8830007
    dcd 0xe5940000
    dcd 0xe893000c
    dcd 0xe3a01002
    bl func_ov107_020c0b90
    dcd 0xe3a00a4b
    dcd 0xe5840014
    dcd 0xe594101c
    mov r0, #0
    dcd 0xe3510000
    dcd 0xda000011
    dcd 0xe1a02000
    dcd 0xe3a01b06
    dcd 0xe1a0c000
    dcd 0xe3a03b02
    dcd 0xe594e014
    dcd 0xe2800001
    dcd 0xe086719e
    dcd 0xe026629e
    dcd 0xe1a0efce
    dcd 0xe0977003
    dcd 0xe026619e
    dcd 0xe0a6600c
    dcd 0xe1a07627
    dcd 0xe1877a06
    dcd 0xe5847014
    dcd 0xe594e01c
    dcd 0xe150000e
    dcd 0xbafffff1
    mov r0, #0
    dcd 0xe5c4003e
    dcd 0xe1d512d0
    dcd 0xe59f2010
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe28dd008
    dcd 0xe8bd80f8
    dcd data_02041dc8
    dcd func_ov220_020d3614
}
