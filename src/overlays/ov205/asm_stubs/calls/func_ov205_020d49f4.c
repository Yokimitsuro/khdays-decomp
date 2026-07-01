extern void VEC_Subtract(void);
extern void data_0203d210(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020c9ee8(void);
extern void func_ov107_020cab14(void);
extern void func_ov205_020d4b6c(void);

asm void func_ov205_020d49f4(void) {

    dcd 0xe92d43f8
    dcd 0xe24dd018
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe3a01000
    dcd 0xe5940000
    bl func_ov107_020cab14
    dcd 0xe5840004
    dcd 0xe3500000
    dcd 0x1a000008
    dcd 0xe5940000
    dcd 0xe3a01002
    dcd 0xe5c011c7
    dcd 0xe1d512d0
    dcd 0xe1a00005
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd018
    dcd 0xe8bd83f8
    dcd 0xe5951000
    dcd 0xe3a0001e
    dcd 0xe591102c
    dcd 0xe59f2104
    dcd 0xe0030091
    dcd 0xe1a00fa3
    dcd 0xe0c31392
    dcd 0xe0803143
    dcd 0xe584303c
    dcd 0xe5940004
    dcd 0xe5941024
    dcd 0xe28d200c
    dcd 0xe2800074
    bl VEC_Subtract
    dcd 0xe28d000c
    dcd 0xe3a02000
    dcd 0xe1a01000
    dcd 0xe58d2010
    bl func_01ff8d18
    dcd 0xe59d000c
    dcd 0xe59d1014
    bl func_020050b4
    dcd 0xe5840038
    dcd 0xe5947034
    dcd 0xe59f30b4
    dcd 0xe59fc0b4
    dcd 0xe0889397
    mov r0, #0
    dcd 0xe58d0004
    dcd 0xe0288c97
    dcd 0xe1a06fc7
    dcd 0xe0288396
    dcd 0xe2993000
    dcd 0xe2a83b02
    dcd 0xe1a03203
    dcd 0xe1a03823
    dcd 0xe1a03243
    dcd 0xe1a06083
    dcd 0xe59fe084
    dcd 0xe1a03086
    dcd 0xe19ec0f3
    dcd 0xe2863001
    dcd 0xe1a03083
    dcd 0xe19e30f3
    dcd 0xe3a00c01
    dcd 0xe28d1000
    dcd 0xe2842008
    dcd 0xe58dc000
    dcd 0xe58d3008
    bl func_01ffa724
    dcd 0xe5940028
    dcd 0xe5d00000
    dcd 0xe3500000
    dcd 0x128dd018
    dcd 0x18bd83f8
    dcd 0xe5940000
    dcd 0xe3a01000
    dcd 0xe5900390
    dcd 0xe3a02001
    bl func_ov107_020c9ee8
    dcd 0xe5940000
    dcd 0xe3a01003
    dcd 0xe3a02001
    bl func_ov107_020c9264
    dcd 0xe1d512d0
    dcd 0xe59f201c
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe28dd018
    dcd 0xe8bd83f8
    dcd 0x66666667
    dcd 0x60db9391
    dcd 0x000028be
    dcd data_0203d210
    dcd func_ov205_020d4b6c
}
