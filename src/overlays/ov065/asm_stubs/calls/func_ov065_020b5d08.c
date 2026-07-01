extern char data_ov065_020b7340[];
extern void func_02030788(void);
extern void func_ov002_020519b0(void);
extern void func_ov002_02052024(void);
extern void func_ov002_020521a4(void);
extern void func_ov022_020a384c(void);
extern void WM_EndKeySharing_0x020b6270(void);
extern void func_ov065_020b6984(void);
extern void func_ov065_020b6998(void);

asm void func_ov065_020b5d08(void)
{
    dcd     0xe92d40f8
    dcd     0xe59f2114
    dcd     0xe1a06001
    dcd     0xe5925000
    dcd     0xe246102e
    dcd     0xe1a07000
    dcd     0xe3510003
    dcd     0xe2854db2
    dcd     0x908ff101
    dcd     0xea00001f
    dcd     0xea000002
    dcd     0xea000006
    dcd     0xea00000b
    dcd     0xea00000a
    dcd     0xe59716bc
    dcd     0xe1510006
    dcd     0x0a000018
    bl      WM_EndKeySharing_0x020b6270
    dcd     0xea000016
    dcd     0xe59716bc
    dcd     0xe1510006
    dcd     0x0a000013
    dcd     0xe1a01004
    bl      func_ov065_020b6984
    dcd     0xea000010
    dcd     0xe59706bc
    dcd     0xe1500006
    dcd     0x0a00000d
    dcd     0xe3560030
    dcd     0x03a00000
    dcd     0x05840000
    dcd     0x0a000006
    dcd     0xe3a00001
    dcd     0xe5840000
    bl      func_02030788
    dcd     0xe5d71008
    dcd     0xe1510000
    dcd     0x03a00000
    dcd     0x05840120
    dcd     0xe1a00007
    dcd     0xe1a01004
    bl      func_ov065_020b6998
    dcd     0xe1a00007
    dcd     0xe1a01006
    bl      func_ov022_020a384c
    dcd     0xe2870c2b
    dcd     0xe1d00bd2
    dcd     0xe3a03000
    dcd     0xe3500002
    dcd     0x03a03001
    dcd     0xe356002e
    dcd     0xba00000c
    dcd     0xe59716bc
    dcd     0xe597200c
    dcd     0xe1a00006
    bl      func_ov002_020519b0
    dcd     0xe285302c
    dcd     0xe2871fc3
    dcd     0xe58d0000
    dcd     0xe2810b03
    dcd     0xe2831b0b
    dcd     0xe1a02006
    dcd     0xe3a03002
    bl      func_ov002_02052024
    dcd     0xe8bd80f8
    dcd     0xe2870fc3
    dcd     0xe285102c
    dcd     0xe1a02006
    dcd     0xe2800b03
    dcd     0xe2811b0b
    bl      func_ov002_020521a4
    dcd     0xe8bd80f8
    dcd     data_ov065_020b7340
}
