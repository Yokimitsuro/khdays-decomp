extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov107_020cab14(void);
extern void func_ov214_020cd0e8(void);

asm void func_ov214_020cd78c(void) {

    dcd 0xe92d4078
    dcd 0xe24dd00c
    dcd 0xe1a06000
    dcd 0xe5965004
    dcd 0xe3a01000
    dcd 0xe5950000
    bl func_ov107_020cab14
    dcd 0xe5850008
    dcd 0xe3500000
    dcd 0x1a000008
    dcd 0xe5950000
    dcd 0xe3a01002
    dcd 0xe5c011c7
    dcd 0xe1d612d0
    dcd 0xe1a00006
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd00c
    dcd 0xe8bd8078
    dcd 0xe5951000
    dcd 0xe28d2000
    dcd 0xe2800e19
    dcd 0xe28110b0
    bl VEC_Subtract
    dcd 0xe28d0000
    dcd 0xe1a01000
    bl func_01ff8d18
    dcd 0xe1a04000
    dcd 0xe59d0000
    dcd 0xe59d1008
    bl func_020050b4
    dcd 0xe585004c
    dcd 0xe1a00006
    dcd 0xe1a01004
    bl func_ov214_020cd0e8
    dcd 0xe3500000
    dcd 0x05950000
    dcd 0x03a01004
    dcd 0x05c011c7
    dcd 0x028dd00c
    dcd 0x08bd8078
    dcd 0xe1d612d0
    dcd 0xe1a00006
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd00c
    dcd 0xe8bd8078
}
