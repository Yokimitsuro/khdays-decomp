extern char data_0204c3d8[];
extern void func_02030788(void);
extern void func_ov002_0205de40(void);
extern void func_ov022_0209145c(void);
extern void func_ov032_020b46e4(void);

asm void func_ov032_020b463c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe2850a02
    dcd     0xe5900644
    dcd     0xe1a04001
    bl      func_ov022_0209145c
    dcd     0xe2850a02
    dcd     0xe5900644
    dcd     0xe1a01004
    dcd     0xe2800030
    bl      func_ov022_0209145c
    dcd     0xe1a00005
    bl      func_ov032_020b46e4
    dcd     0xe2850a02
    dcd     0xe5900644
    dcd     0xe5d04018
    dcd     0xe1a00004
    bl      func_ov002_0205de40
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000010
    dcd     0xe3540000
    dcd     0xca000006
    dcd     0xe5951000
    dcd     0xe5950004
    dcd     0xe3811302
    dcd     0xe5851000
    dcd     0xe3800000
    dcd     0xe5850004
    dcd     0xea000007
    dcd     0xe3e01000
    dcd     0xe5952004
    dcd     0xe5953000
    dcd     0xe2410302
    dcd     0xe0030000
    dcd     0xe5850000
    dcd     0xe0020001
    dcd     0xe5850004
    dcd     0xe59f0004
    dcd     0xe5c04110
    dcd     0xe8bd8038
    dcd     data_0204c3d8
}
