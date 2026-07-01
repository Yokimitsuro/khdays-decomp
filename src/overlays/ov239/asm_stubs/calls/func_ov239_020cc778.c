extern void func_ov107_020c8eb8(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_ov107_020ca918(void);
extern void VEC_Add(void);
extern void func_ov107_020c0b90(void);
extern void func_ov107_020c5af8(void);
extern void data_02042258(void);

asm void func_ov239_020cc778(void)
{
    dcd     0xe92d4ff8
    dcd     0xe24dd050
    dcd     0xe1a0a000
    mov r0, #0
    dcd     0xe1a05001
    dcd     0xe3520000
    dcd     0xe58d0008
    dcd     0x0a000003
    dcd     0xe28d4040
    dcd     0xe892000f
    dcd     0xe884000f
    dcd     0xea000007
    dcd     0xe59a0000
    dcd     0xe28d3040
    dcd     0xe2800074
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe59a0000
    dcd     0xe5900080
    dcd     0xe58d004c
    dcd     0xe59a0000
    dcd     0xe28d1040
    dcd     0xe28d2030
    bl      func_ov107_020c8eb8
    dcd     0xe1a08000
    dcd     0xe3580000
    dcd     0xe3a07000
    dcd     0xda00004c
    dcd     0xe59f0158
    dcd     0xe28d300c
    dcd     0xe8900007
    dcd     0xe205b0ff
    dcd     0xe8830007
    dcd     0xe24d4008
    dcd     0xe28d6024
    dcd     0xe28d5018
    dcd     0xe28d0030
    dcd     0xe7903107
    mov r0, #1
    dcd     0xe1d320b2
    dcd     0xe5da1030
    dcd     0xe1a00210
    dcd     0xe20090ff
    dcd     0xe1110009
    dcd     0x1a000038
    dcd     0xe59a1000
    dcd     0xe2830074
    dcd     0xe1a02006
    dcd     0xe2811074
    bl      VEC_Subtract
    dcd     0xe1a00006
    dcd     0xe1a01005
    bl      func_01ff8d18
    mov r0, #0
    dcd     0xe58d0028
    dcd     0xe1a00006
    dcd     0xe1a01006
    bl      func_01ff8d18
    dcd     0xe3500000
    dcd     0x028d000c
    dcd     0x08900007
    dcd     0x08860007
    dcd     0xe3a00b02
    dcd     0xe1a01006
    dcd     0xe1a02006
    bl      func_01ffa724
    dcd     0xe59a1000
    mov r0, #0
    dcd     0xe58d6000
    dcd     0xe58d0004
    dcd     0xe28d0030
    dcd     0xe7900107
    dcd     0xe1a0300b
    dcd     0xe1a02001
    bl      func_ov107_020ca918
    dcd     0xe3500000
    dcd     0x0a000018
    dcd     0xe59d004c
    dcd     0xe1a01005
    dcd     0xe1a02005
    bl      func_01ffa724
    dcd     0xe1a00005
    dcd     0xe1a01006
    dcd     0xe1a02005
    bl      VEC_Add
    dcd     0xe1a00005
    dcd     0xe28d1040
    dcd     0xe1a02005
    bl      VEC_Add
    mov r0, #0
    dcd     0xe58d0004
    dcd     0xe8950007
    dcd     0xe8840007
    dcd     0xe59a0000
    dcd     0xe3a01003
    dcd     0xe894000c
    bl      func_ov107_020c0b90
    mov r0, #1
    dcd     0xe5da1030
    dcd     0xe58d0008
    dcd     0xe1810009
    dcd     0xe5ca0030
    dcd     0xe2877001
    dcd     0xe1570008
    dcd     0xbaffffba
    dcd     0xe59d0008
    dcd     0xe3500000
    dcd     0x028dd050
    dcd     0x08bd8ff8
    dcd     0xe59a0000
    dcd     0xe59a3008
    dcd     0xe3a01f4e
    dcd     0xe3a02006
    bl      func_ov107_020c5af8
    dcd     0xe28dd050
    dcd     0xe8bd8ff8
    dcd     data_02042258
}
