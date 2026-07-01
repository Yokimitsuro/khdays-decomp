extern void func_0202fafc(void);
extern void func_0202fb58(void);
extern void func_ov012_0205bbac(void);
extern void func_ov012_0205bcf0(void);

asm void func_ov012_0205c0e0(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd00c
    dcd     0xe1a05000
    dcd     0xe1a00005
    bl      func_ov012_0205bcf0
    dcd     0xe1a02000
    dcd     0xe3520001
    dcd     0x0afffffa
    dcd     0xe3520000
    dcd     0x0a00002f
    dcd     0xe28d1004
    dcd     0xe1a00005
    bl      func_0202fafc
    dcd     0xe59d0004
    dcd     0xe5952088
    dcd     0xe1d030d2
    dcd     0xe5951058
    dcd     0xe5950040
    dcd     0xe0834002
    dcd     0xe0811004
    dcd     0xe1510000
    dcd     0xda000005
    dcd     0xe1a00005
    bl      func_ov012_0205bbac
    dcd     0xe3500000
    dcd     0x028dd00c
    dcd     0x03a00000
    dcd     0x08bd8030
    dcd     0xe28d1004
    dcd     0xe58d1000
    dcd     0xe1d534b8
    dcd     0xe595c058
    dcd     0xe1d514bc
    dcd     0xe595205c
    dcd     0xe08c3003
    dcd     0xe0822001
    dcd     0xe2831001
    dcd     0xe1a00005
    dcd     0xe2822001
    dcd     0xe3a03002
    bl      func_0202fb58
    dcd     0xe28d1004
    dcd     0xe58d1000
    dcd     0xe1d514b8
    dcd     0xe595e058
    dcd     0xe1d524bc
    dcd     0xe595c05c
    dcd     0xe5953060
    dcd     0xe1a00005
    dcd     0xe08e1001
    dcd     0xe08c2002
    bl      func_0202fb58
    dcd     0xe5951058
    dcd     0xe28dd00c
    dcd     0xe0811004
    mov r0, #1
    dcd     0xe5851058
    dcd     0xe8bd8030
    mov r0, #0
    dcd     0xe28dd00c
    dcd     0xe8bd8030
}
