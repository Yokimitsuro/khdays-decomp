extern void func_ov297_020d4168(void);
extern void func_ov297_020d4240(void);
extern void func_0203c634(void);
extern void func_ov297_020d5354(void);

asm void func_ov297_020d52c0(void)
{
    dcd     0xe92d4038
    dcd     0xe1a04000
    dcd     0xe5945004
    bl      func_ov297_020d4168
    dcd     0xe1a00004
    bl      func_ov297_020d4240
    dcd     0xe5950060
    dcd     0xe3500004
    dcd     0xba00000a
    dcd     0xe5950080
    dcd     0xe3500000
    dcd     0x1a000007
    dcd     0xe5950000
    dcd     0xe3a0100a
    dcd     0xe5c011c7
    dcd     0xe1d412d0
    dcd     0xe1a00004
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     0xe595007c
    dcd     0xe3500004
    dcd     0xba000007
    dcd     0xe5950000
    dcd     0xe3a01009
    dcd     0xe5c011c7
    dcd     0xe1d412d0
    dcd     0xe1a00004
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     0xe1d412d0
    dcd     0xe59f2008
    dcd     0xe1a00004
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov297_020d5354
}
