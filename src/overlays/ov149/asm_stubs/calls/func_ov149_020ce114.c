extern void VEC_Mag(void);
extern void VEC_Subtract(void);
extern void func_01fffd70(void);
extern void func_01fffd8c(void);
extern void func_ov107_020c09a0(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020c7500(void);
extern void func_ov107_020cb040(void);
extern void func_ov149_020d04f8(void);

asm void func_ov149_020ce114(void) {

    dcd 0xe92d4ff0
    dcd 0xe24dd03c
    dcd 0xe58d1008
    dcd 0xe5d11002
    dcd 0xe1a0a000
    dcd 0xe58d200c
    dcd 0xe3510005
    dcd 0x1a000087
    dcd 0xe59d0008
    dcd 0xe5d00003
    dcd 0xe3500000
    dcd 0x0a000032
    dcd 0xe3500001
    dcd 0x0a000002
    dcd 0xe3500002
    dcd 0x0a000021
    dcd 0xea00007e
    mov r0, #0
    dcd 0xe58d0000
    dcd 0xe58d0004
    dcd 0xe59a1390
    dcd 0xe59a2394
    dcd 0xe59a003c
    dcd 0xe5911008
    dcd 0xe2823004
    dcd 0xe3a02017
    bl func_ov107_020c09a0
    dcd 0xe59a2390
    dcd 0xe3a01000
    dcd 0xe582000c
    dcd 0xe58d1000
    dcd 0xe58d1004
    dcd 0xe59a1390
    dcd 0xe59a003c
    dcd 0xe5911018
    dcd 0xe28a3fe7
    dcd 0xe3a02017
    bl func_ov107_020c09a0
    dcd 0xe59a2390
    dcd 0xe59f11b4
    dcd 0xe582001c
    dcd 0xe59a2394
    dcd 0xe1a0000a
    dcd 0xe2822004
    dcd 0xe58d2000
    dcd 0xe3a02007
    dcd 0xe3a03000
    bl func_ov107_020cb040
    dcd 0xe58a03d0
    dcd 0xea00005d
    mov r0, #0
    dcd 0xe58d0000
    dcd 0xe58d0004
    dcd 0xe59a1390
    dcd 0xe59a2394
    dcd 0xe59a003c
    dcd 0xe5911020
    dcd 0xe2823004
    dcd 0xe3a02017
    bl func_ov107_020c09a0
    dcd 0xe59a1390
    dcd 0xe5810024
    dcd 0xea000050
    dcd 0xe59a7004
    dcd 0xe28d201c
    dcd 0xe3a01004
    mov r0, #0
    dcd 0xe1c200b0
    dcd 0xe1c200b2
    dcd 0xe1c200b4
    dcd 0xe1c200b6
    dcd 0xe2822008
    dcd 0xe2511001
    dcd 0x1afffff8
    dcd 0xe2870080
    dcd 0xe3a08000
    bl func_01fffd70
    dcd 0xe3500000
    dcd 0x01a09008
    dcd 0x15909000
    dcd 0xe3590000
    dcd 0x0a000038
    dcd 0xe59fb108
    dcd 0xe3a04000
    dcd 0xe28d501c
    dcd 0xe28d6010
    dcd 0xe1d906b0
    dcd 0xe1a00c00
    dcd 0xe1a00c20
    dcd 0xe3100001
    dcd 0x0a000028
    dcd 0xe2890c01
    dcd 0xe1d00abc
    dcd 0xe3100004
    dcd 0x1a000024
    dcd 0xe1a02006
    dcd 0xe2890074
    dcd 0xe28a1074
    bl VEC_Subtract
    dcd 0xe1a00006
    bl VEC_Mag
    dcd 0xe5992080
    dcd 0xe59a1080
    dcd 0xe0821001
    dcd 0xe0400001
    dcd 0xe3500902
    dcd 0xca000018
    dcd 0xe1d910b2
    dcd 0xe1a00088
    dcd 0xe2888001
    dcd 0xe18510b0
    dcd 0xe59a0050
    dcd 0xe3500001
    dcd 0x1a00000f
    dcd 0xe2891c02
    dcd 0xe1d101f8
    dcd 0xe1d121fa
    dcd 0xe0801fa0
    dcd 0xe09210c1
    dcd 0x41a00004
    dcd 0x4a000001
    dcd 0xe1510000
    dcd 0xd1a00001
    dcd 0xe2891c02
    dcd 0xe1c101ba
    dcd 0xe1a0000a
    dcd 0xe1a0100b
    dcd 0xe2893074
    dcd 0xe3a02008
    bl func_ov107_020c5af8
    dcd 0xe3580010
    dcd 0xaa000006
    dcd 0xe2870080
    bl func_01fffd8c
    dcd 0xe3500000
    dcd 0x03a09000
    dcd 0x15909000
    dcd 0xe3590000
    dcd 0x1affffca
    dcd 0xe28d101c
    dcd 0xe1a0000a
    bl func_ov149_020d04f8
    dcd 0xe59a1390
    dcd 0xe5810004
    dcd 0xe59d1008
    dcd 0xe59d200c
    dcd 0xe1a0000a
    bl func_ov107_020c7500
    dcd 0xe28dd03c
    dcd 0xe8bd8ff0
    dcd 0x0000014e
}
