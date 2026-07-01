extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_ov107_020c0b90(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020c8eb8(void);
extern void func_ov107_020c8f44(void);
extern void func_ov107_020ca918(void);

asm void func_ov169_020ce424(void)
{
    dcd     0xe92d4ff0
    dcd     0xe24dd024
    dcd     0xe1a0a000
    dcd     0xe3520000
    dcd     0xe3a0b000
    dcd     0x0a000006
    dcd     0xe59a0000
    dcd     0xe1a01002
    dcd     0xe590038c
    dcd     0xe28d2014
    bl      func_ov107_020c8f44
    dcd     0xe1a08000
    dcd     0xea00000a
    dcd     0xe3510000
    dcd     0x0a000005
    dcd     0xe59a0000
    dcd     0xe28d2014
    dcd     0xe590038c
    bl      func_ov107_020c8eb8
    dcd     0xe1a08000
    dcd     0xea000002
    dcd     0xe28dd024
    dcd     0xe1a0000b
    dcd     0xe8bd8ff0
    dcd     0xe3580000
    dcd     0xe3a07000
    dcd     0xda00003a
    dcd     0xe24d4008
    dcd     0xe28d5008
    dcd     0xe28d6014
    dcd     0xe7963107
    mov r0, #1
    dcd     0xe1d320b2
    dcd     0xe5da1048
    dcd     0xe1a00210
    dcd     0xe20090ff
    dcd     0xe1110009
    dcd     0x1a00002c
    dcd     0xe59a1000
    dcd     0xe2830074
    dcd     0xe1a02005
    dcd     0xe2811074
    bl      VEC_Subtract
    mov r0, #0
    dcd     0xe58d000c
    dcd     0xe1a00005
    dcd     0xe1a01005
    bl      func_01ff8d18
    dcd     0xe3a00b02
    dcd     0xe1a01005
    dcd     0xe1a02005
    bl      func_01ffa724
    dcd     0xe3a00a01
    dcd     0xe58d000c
    dcd     0xe59a1000
    dcd     0xe3a03000
    dcd     0xe58d5000
    dcd     0xe1a00003
    dcd     0xe58d0004
    dcd     0xe7960107
    dcd     0xe591238c
    bl      func_ov107_020ca918
    dcd     0xe3500000
    dcd     0x0a000012
    mov r0, #0
    dcd     0xe58d0004
    dcd     0xe59a0008
    dcd     0xe8900007
    dcd     0xe8840007
    dcd     0xe59a0000
    dcd     0xe3a01002
    dcd     0xe590038c
    dcd     0xe894000c
    bl      func_ov107_020c0b90
    dcd     0xe59a0000
    dcd     0xe59a3008
    dcd     0xe3a01000
    dcd     0xe3a02053
    bl      func_ov107_020c5af8
    dcd     0xe5da0048
    dcd     0xe3a0b001
    dcd     0xe1800009
    dcd     0xe5ca0048
    dcd     0xe2877001
    dcd     0xe1570008
    dcd     0xbaffffc7
    dcd     0xe35b0000
    dcd     0x0a000004
    dcd     0xe59a0000
    dcd     0xe59a3008
    dcd     0xe59f1010
    dcd     0xe3a02006
    bl      func_ov107_020c5af8
    dcd     0xe1a0000b
    dcd     0xe28dd024
    dcd     0xe8bd8ff0
    dcd     0x0000013f
}
