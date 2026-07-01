extern void func_ov002_020519b0(void);
extern void func_ov002_02052024(void);
extern void func_ov002_020521a4(void);
extern void func_ov022_020a384c(void);
extern void func_ov097_020bb210(void);
extern void func_ov097_020bb840(void);

asm void func_ov097_020baad0(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd004
    dcd     0xe1a05000
    dcd     0xe1a04001
    dcd     0xe2850084
    dcd     0xe354002e
    dcd     0xe2806b0b
    dcd     0x0a000015
    dcd     0xe354002f
    dcd     0x0a000002
    dcd     0xe3540030
    dcd     0x0a000008
    dcd     0xea000010
    dcd     0xe59506bc
    dcd     0xe1500004
    dcd     0x0a00000d
    dcd     0xe1a00006
    bl      func_ov097_020bb210
    dcd     0xe3a00000
    dcd     0xe5860664
    dcd     0xea000008
    dcd     0xe59506bc
    dcd     0xe1500004
    dcd     0x0a000005
    dcd     0xe2860e11
    bl      func_ov097_020bb210
    dcd     0xe2860e22
    bl      func_ov097_020bb840
    dcd     0xe3a00001
    dcd     0xe5860664
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov022_020a384c
    dcd     0xe2850c2b
    dcd     0xe1d00bd2
    dcd     0xe3a03000
    dcd     0xe3500002
    dcd     0x03a03001
    dcd     0xe354002e
    dcd     0xba00000d
    dcd     0xe59516bc
    dcd     0xe595200c
    dcd     0xe1a00004
    bl      func_ov002_020519b0
    dcd     0xe2853ec3
    dcd     0xe2851fc3
    dcd     0xe58d0000
    dcd     0xe2810b03
    dcd     0xe2831a02
    dcd     0xe1a02004
    dcd     0xe3a03002
    bl      func_ov002_02052024
    dcd     0xe28dd004
    dcd     0xe8bd8078
    dcd     0xe2850fc3
    dcd     0xe2851ec3
    dcd     0xe1a02004
    dcd     0xe2800b03
    dcd     0xe2811a02
    bl      func_ov002_020521a4
    dcd     0xe28dd004
    dcd     0xe8bd8078
}
