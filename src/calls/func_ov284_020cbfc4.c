extern void MTX_Identity33_(void);
extern char data_02047394[];
extern char data_02047428[];
extern void func_0201574c(void);
extern void func_02015880(void);
extern void func_020279e0(void);

asm void func_ov284_020cbfc4(void)
{
    dcd     0xe92d40f8
    dcd     0xe1a06000
    dcd     0xe59f0068
    bl      MTX_Identity33_
    dcd     0xe596008c
    dcd     0xe3a04000
    dcd     0xe3500000
    dcd     0xd8bd80f8
    dcd     0xe59f7054
    dcd     0xe1a05004
    dcd     0xe5961090
    dcd     0xe7910005
    dcd     0xe0811005
    dcd     0xe3500000
    dcd     0x0a000008
    dcd     0xe58700c4
    dcd     0xe58700c8
    dcd     0xe58700cc
    dcd     0xe281002c
    bl      func_02015880
    bl      func_0201574c
    dcd     0xe5960088
    dcd     0xe2800020
    bl      func_020279e0
    dcd     0xe596008c
    dcd     0xe2844001
    dcd     0xe1540000
    dcd     0xe2855038
    dcd     0xbaffffec
    dcd     0xe8bd80f8
    dcd     data_02047428
    dcd     data_02047394
}
