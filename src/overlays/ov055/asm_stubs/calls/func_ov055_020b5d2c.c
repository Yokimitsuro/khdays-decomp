extern void WM_EndKeySharing_0x020b6128(void);
extern void func_ov055_020b7368(void);
extern void func_ov022_020a384c(void);
extern void func_ov002_020519b0(void);
extern void func_ov002_02052024(void);
extern void func_ov002_020521a4(void);
extern void data_ov055_020b7740(void);

asm void func_ov055_020b5d2c(void)
{
    dcd     0xe92d40f8
    dcd     0xe59f20bc
    dcd     0xe1a05001
    dcd     0xe1a06000
    dcd     0xe355002e
    dcd     0xe5924000
    dcd     0x0a000002
    dcd     0xe355002f
    dcd     0x13550030
    dcd     0xea000003
    dcd     0xe59616bc
    dcd     0xe1510005
    dcd     0x0a000000
    bl      WM_EndKeySharing_0x020b6128
    dcd     0xe59606bc
    dcd     0xe1500005
    dcd     0x0a000001
    dcd     0xe1a00006
    bl      func_ov055_020b7368
    dcd     0xe1a00006
    dcd     0xe1a01005
    bl      func_ov022_020a384c
    dcd     0xe2860c2b
    dcd     0xe1d00bd2
    dcd     0xe59616bc
    dcd     0xe596200c
    dcd     0xe3500002
    dcd     0xe3a07000
    dcd     0xe1a00005
    dcd     0x03a07001
    bl      func_ov002_020519b0
    dcd     0xe355002e
    dcd     0xba000008
    dcd     0xe284302c
    dcd     0xe2861f6a
    dcd     0xe58d0000
    dcd     0xe2810b03
    dcd     0xe2831b0b
    dcd     0xe1a02005
    dcd     0xe3a03002
    bl      func_ov002_02052024
    dcd     0xe8bd80f8
    dcd     0xe2860f6a
    dcd     0xe284102c
    dcd     0xe1a02005
    dcd     0xe1a03007
    dcd     0xe2800b03
    dcd     0xe2811b0b
    bl      func_ov002_020521a4
    dcd     0xe8bd80f8
    dcd     data_ov055_020b7740
}
