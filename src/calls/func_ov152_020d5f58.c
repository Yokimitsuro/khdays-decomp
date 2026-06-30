extern void VEC_Add(void);
extern void func_01ffa724(void);
extern void func_0202f384(void);
extern void func_0203c634(void);
extern void func_ov107_020c9f48(void);

asm void func_ov152_020d5f58(void) {

    dcd 0xe92d4078
    dcd 0xe24dd00c
    dcd 0xe1a04000
    dcd 0xe5946004
    dcd 0xe28d1000
    dcd 0xe5960000
    dcd 0xe59003cc
    bl func_ov107_020c9f48
    dcd 0xe5961000
    dcd 0xe1a05000
    dcd 0xe28d2000
    dcd 0xe2860018
    dcd 0xe28110a0
    bl func_0202f384
    dcd 0xe2861018
    dcd 0xe1a00005
    dcd 0xe1a02001
    bl func_01ffa724
    dcd 0xe2860018
    dcd 0xe2861024
    dcd 0xe1a02000
    bl VEC_Add
    dcd 0xe2861024
    dcd 0xe3a00c0b
    dcd 0xe1a02001
    bl func_01ffa724
    dcd 0xe5960048
    dcd 0xe5d00000
    dcd 0xe3500000
    dcd 0x128dd00c
    dcd 0x18bd8078
    dcd 0xe5961000
    dcd 0xe5d1017a
    dcd 0xe1a00f80
    dcd 0xe1b00fa0
    dcd 0x1a000004
    dcd 0xe5d1017c
    dcd 0xe1a00f80
    dcd 0xe1b00fa0
    dcd 0x028dd00c
    dcd 0x08bd8078
    dcd 0xe3a00002
    dcd 0xe5c101c7
    dcd 0xe1d412d0
    dcd 0xe1a00004
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd00c
    dcd 0xe8bd8078
}
