extern void func_ov002_020573cc(void);
extern void func_ov002_020766e0(void);

asm void func_ov014_020803c0(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd008
    dcd     0xe1a05000
    dcd     0xe2850c01
    dcd     0xe1d003d4
    dcd     0xe1a04001
    dcd     0xe3500000
    dcd     0x128dd008
    dcd     0x13a00000
    dcd     0x18bd8038
    bl      func_ov002_020573cc
    dcd     0xe3500000
    dcd     0x128dd008
    dcd     0x13a00000
    dcd     0x18bd8038
    dcd     0xe3a00001
    dcd     0xe5cd0000
    dcd     0xe5d43000
    dcd     0xe28d1000
    dcd     0xe1a00005
    dcd     0xe3a02006
    dcd     0xe5cd3004
    bl      func_ov002_020766e0
    dcd     0xe3a00001
    dcd     0xe5c50134
    dcd     0xe3a00000
    dcd     0xe28dd008
    dcd     0xe8bd8038
}
