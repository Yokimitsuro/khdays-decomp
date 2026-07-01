extern void func_0202ba9c(void);
extern void func_ov002_0207285c(void);
extern void func_ov002_02073ed0(void);
extern void func_ov002_02074460(void);

asm void func_ov014_0207fb88(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe5d40010
    bl      func_ov002_0207285c
    dcd     0xe1a01800
    dcd     0xe3a02000
    dcd     0xe1a03002
    dcd     0xe284002c
    dcd     0xe1a01821
    bl      func_0202ba9c
    dcd     0xe5d401b1
    dcd     0xe3100080
    dcd     0x18bd8010
    dcd     0xe2840c01
    dcd     0xe1d00df0
    dcd     0xe3500000
    dcd     0xb8bd8010
    bl      func_ov002_02074460
    dcd     0xe3500000
    dcd     0xb8bd8010
    dcd     0xe2840c01
    dcd     0xe1d00df0
    dcd     0xe3a01000
    dcd     0xe2412001
    bl      func_ov002_02073ed0
    dcd     0xe8bd8010
}
