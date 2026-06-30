extern void func_02023eb4(void);
extern void func_ov239_020cc9f0(void);
extern void func_ov239_020cd028(void);

asm void func_ov239_020ccfcc(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd004
    dcd     0xe1a04000
    dcd     0xe5945004
    dcd     0xe5950000
    dcd     0xe5906224
    dcd     0xe5900228
    dcd     0xe0500006
    dcd     0x42600000
    dcd     0xe2800001
    bl      func_02023eb4
    dcd     0xe0860000
    dcd     0xe585002c
    dcd     0xe59fc01c
    dcd     0xe1a00004
    dcd     0xe3a01002
    dcd     0xe3a02000
    dcd     0xe3a03001
    dcd     0xe58dc000
    bl      func_ov239_020cc9f0
    dcd     0xe28dd004
    dcd     0xe8bd8078
    dcd     func_ov239_020cd028
}
