extern void func_01ffa724(void);
extern void func_0202f384(void);
extern void func_0203c634(void);
extern void func_ov107_020c9f48(void);
extern void func_ov204_020d1518(void);

asm void func_ov204_020d14a0(void) {

    dcd 0xe92d4078
    dcd 0xe24dd00c
    dcd 0xe1a06000
    dcd 0xe5965004
    dcd 0xe28d1000
    dcd 0xe5950000
    dcd 0xe5900390
    bl func_ov107_020c9f48
    dcd 0xe5951000
    dcd 0xe1a04000
    dcd 0xe28d2000
    dcd 0xe2850008
    dcd 0xe28110a0
    bl func_0202f384
    dcd 0xe2851008
    dcd 0xe1a00004
    dcd 0xe1a02001
    bl func_01ffa724
    dcd 0xe5950028
    dcd 0xe5d00000
    dcd 0xe3500000
    dcd 0x128dd00c
    dcd 0x18bd8078
    dcd 0xe1d612d0
    dcd 0xe59f200c
    dcd 0xe1a00006
    bl func_0203c634
    dcd 0xe28dd00c
    dcd 0xe8bd8078
    dcd func_ov204_020d1518
}
