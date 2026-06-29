extern char data_ov037_020b4e20[];
extern void func_ov022_020a384c(void);
extern void func_ov037_020b4340(void);
extern void func_ov037_020b4354(void);
extern void func_ov037_020b459c(void);

asm void func_ov037_020b355c(void)
{
    dcd     0xe92d41f0
    dcd     0xe59f20bc
    dcd     0xe1a07001
    dcd     0xe5921000
    dcd     0xe1a08000
    dcd     0xe281102c
    dcd     0xe357002e
    dcd     0xe2814b0b
    dcd     0xe3e05000
    dcd     0xe3a06001
    dcd     0x0a000004
    dcd     0xe357002f
    dcd     0x0a000008
    dcd     0xe3570030
    dcd     0x0a00000e
    dcd     0xea000019
    dcd     0xe59816bc
    dcd     0xe1510007
    dcd     0x0a000016
    dcd     0xe1a01004
    bl      func_ov037_020b4340
    dcd     0xea000013
    dcd     0xe3a01000
    dcd     0xe5841114
    dcd     0xe59816bc
    dcd     0xe1510007
    dcd     0x0a00000e
    dcd     0xe1a01004
    bl      func_ov037_020b459c
    dcd     0xea00000b
    dcd     0xe5846114
    dcd     0xe59816bc
    dcd     0xe1510007
    dcd     0x03a06000
    dcd     0x0a000004
    dcd     0xe1a01004
    bl      func_ov037_020b4354
    dcd     0xe1a00008
    dcd     0xe1a01004
    bl      func_ov037_020b459c
    dcd     0xe3a05030
    dcd     0xe3a0702f
    dcd     0xe3560000
    dcd     0x0a000002
    dcd     0xe1a00008
    dcd     0xe1a01007
    bl      func_ov022_020a384c
    dcd     0xe3550000
    dcd     0xa58856bc
    dcd     0xe8bd81f0
    dcd     data_ov037_020b4e20
}
