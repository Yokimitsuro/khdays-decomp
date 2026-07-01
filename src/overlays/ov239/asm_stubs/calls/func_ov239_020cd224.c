extern void func_ov107_020c5af8(void);
extern void func_0202f384(void);
extern void VEC_Add(void);
extern void func_ov239_020cc778(void);
extern void func_0203c634(void);

asm void func_ov239_020cd224(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd010
    dcd     0xe1a05000
    dcd     0xe8950011
    dcd     0xe594102c
    dcd     0xe590002c
    dcd     0xe0810000
    dcd     0xe584002c
    dcd     0xe5d40032
    dcd     0xe3500000
    dcd     0x1a000009
    dcd     0xe594002c
    dcd     0xe3500e33
    dcd     0xba000006
    dcd     0xe5940000
    dcd     0xe5943008
    dcd     0xe3a01f4e
    dcd     0xe3a02005
    bl      func_ov107_020c5af8
    mov r0, #1
    dcd     0xe5c40032
    dcd     0xe594002c
    dcd     0xe3500d11
    dcd     0xba000018
    dcd     0xe3500d22
    dcd     0xca000016
    dcd     0xe5941000
    dcd     0xe3a03000
    dcd     0xe591c080
    dcd     0xe59f1080
    dcd     0xe3a02c01
    dcd     0xe58dc00c
    dcd     0xe58d3000
    dcd     0xe58d2004
    dcd     0xe58d1008
    dcd     0xe5941000
    dcd     0xe28d0000
    dcd     0xe1a02000
    dcd     0xe28110a0
    bl      func_0202f384
    dcd     0xe5941000
    dcd     0xe28d0000
    dcd     0xe2811074
    dcd     0xe1a02000
    bl      VEC_Add
    dcd     0xe28d2000
    dcd     0xe1a00004
    dcd     0xe3a01000
    bl      func_ov239_020cc778
    dcd     0xe5940004
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x128dd010
    dcd     0x18bd8038
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd010
    dcd     0xe8bd8038
    dcd     0x00001350
}
