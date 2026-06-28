extern void func_ov045_020b48b4(void);
extern void func_ov045_020b41c8(void);
extern void func_ov022_020a384c(void);
extern void func_ov002_020519b0(void);
extern void func_ov002_02052024(void);
extern void func_ov002_020521a4(void);

asm void func_ov045_020b3684(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd004
    dcd     0xe1a04001
    dcd     0xe1a05000
    dcd     0xe354002e
    dcd     0x0a000003
    dcd     0xe354002f
    dcd     0x13540030
    dcd     0x0a000005
    dcd     0xea00000b
    dcd     0xe59516bc
    dcd     0xe1540001
    dcd     0x0a000008
    bl      func_ov045_020b48b4
    dcd     0xea000006
    dcd     0xe59506bc
    dcd     0xe1540000
    dcd     0x0a000003
    dcd     0xe2851edf
    dcd     0xe1a00005
    dcd     0xe2811a02
    bl      func_ov045_020b41c8
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov022_020a384c
    dcd     0xe2850c2b
    dcd     0xe1d00bd2
    dcd     0xe59516bc
    dcd     0xe595200c
    dcd     0xe3500002
    dcd     0xe3a06000
    dcd     0xe1a00004
    dcd     0x03a06001
    bl      func_ov002_020519b0
    dcd     0xe354002e
    dcd     0xba000009
    dcd     0xe2853f4e
    dcd     0xe2851f6a
    dcd     0xe58d0000
    dcd     0xe2810b03
    dcd     0xe2831b0b
    dcd     0xe1a02004
    dcd     0xe3a03002
    bl      func_ov002_02052024
    dcd     0xe28dd004
    dcd     0xe8bd8078
    dcd     0xe2850f6a
    dcd     0xe2851f4e
    dcd     0xe1a02004
    dcd     0xe1a03006
    dcd     0xe2800b03
    dcd     0xe2811b0b
    bl      func_ov002_020521a4
    dcd     0xe28dd004
    dcd     0xe8bd8078
}
