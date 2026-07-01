extern void func_020119d4(void);
extern void func_02024c94(void);
extern void func_02025464(void);
extern void func_020255d4(void);

asm void func_ov003_0204d308(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd004
    dcd     0xe1a06001
    dcd     0xe2861a01
    dcd     0xe591cdbc
    dcd     0xe1a04000
    dcd     0xe1a05003
    dcd     0xe35c0000
    dcd     0x1a000005
    dcd     0xe59d4018
    dcd     0xe58d4000
    dcd     0xe5911db8
    bl      func_02024c94
    dcd     0xe28dd004
    dcd     0xe8bd8078
    dcd     0xe59dc018
    dcd     0xe3e03000
    dcd     0xe58dc000
    dcd     0xe5911db8
    bl      func_02024c94
    dcd     0xe2860a01
    dcd     0xe5900dbc
    dcd     0xe3a01000
    bl      func_02025464
    dcd     0xe3550000
    dcd     0xb28dd004
    dcd     0xb8bd8078
    dcd     0xe2860a01
    dcd     0xe5900dbc
    dcd     0xe1a02005
    dcd     0xe3a01001
    bl      func_020255d4
    dcd     0xe3500000
    dcd     0x028dd004
    dcd     0x08bd8078
    dcd     0xe2841004
    bl      func_020119d4
    dcd     0xe3500000
    dcd     0x03a00000
    dcd     0x05840004
    dcd     0xe28dd004
    dcd     0xe8bd8078
}
