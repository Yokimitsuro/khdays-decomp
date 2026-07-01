extern void func_01fffde0(void);
extern void func_01fffe14(void);
extern void func_0202aa9c(void);
extern void func_02030670(void);
extern void func_ov002_0206b758(void);
extern void func_ov002_0207c618(void);
extern void func_ov014_020801d0(void);
extern void func_ov014_02080344(void);
extern void func_ov014_02080520(void);
extern void func_ov022_020ad2e4(void);

asm void func_ov014_02080464(void)
{
    dcd     0xe92d4038
    dcd     0xe1a04000
    dcd     0xe3a05000
    bl      func_02030670
    dcd     0xe3500000
    dcd     0x1a000003
    dcd     0xe1d401b2
    dcd     0xe3100002
    dcd     0x01a00005
    dcd     0x08bd8038
    bl      func_ov002_0206b758
    dcd     0xe3500000
    dcd     0x0a000007
    dcd     0xe1a00004
    bl      func_ov014_02080344
    dcd     0xe3500000
    dcd     0x0a000003
    bl      func_01fffe14
    bl      func_01fffde0
    dcd     0xe3a01001
    bl      func_ov022_020ad2e4
    dcd     0xe2840c01
    dcd     0xe1d003d4
    dcd     0xe3500002
    dcd     0x0a000002
    dcd     0xe3500003
    dcd     0x059f5048
    dcd     0xea00000a
    dcd     0xe1a00004
    bl      func_ov014_020801d0
    dcd     0xe1d401b2
    dcd     0xe3100004
    dcd     0x0a000004
    dcd     0xe2840c01
    dcd     0xe1d013d5
    dcd     0xe284002c
    dcd     0xe3a02000
    bl      func_ov002_0207c618
    dcd     0xe59f5018
    dcd     0xe1d401b2
    dcd     0xe3100004
    dcd     0x0a000001
    dcd     0xe284002c
    bl      func_0202aa9c
    dcd     0xe1a00005
    dcd     0xe8bd8038
    dcd     func_ov014_02080520
}
