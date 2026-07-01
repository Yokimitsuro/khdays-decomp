extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov261_020d0f90(void);

asm void func_ov261_020d0e4c(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd018
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a00024
    dcd     0xe5942000
    dcd     0xe5d41049
    dcd     0xe59223a0
    dcd     0xe28d300c
    dcd     0xe0202091
    dcd     0xe280002c
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5941004
    dcd     0xe28d2000
    dcd     0xe1a00003
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe3a02000
    dcd     0xe1a01000
    dcd     0xe58d2004
    bl      func_01ff8d18
    dcd     0xe3a02c01
    dcd     0xe3500c01
    dcd     0xb1a02000
    dcd     0xe1a00002
    dcd     0xe28d1000
    dcd     0xe2842030
    bl      func_01ffa724
    dcd     0xe5951000
    dcd     0xe3a0001e
    dcd     0xe591202c
    dcd     0xe59f10b0
    dcd     0xe0030092
    dcd     0xe0c20391
    dcd     0xe0832002
    dcd     0xe1a00fa3
    dcd     0xe0802242
    dcd     0xe584203c
    dcd     0xe5940000
    dcd     0xe59f2094
    dcd     0xe590013c
    dcd     0xe594c034
    dcd     0xe2601a02
    dcd     0xe1a00fa1
    dcd     0xe0c31192
    dcd     0xe0803243
    dcd     0xe08c0003
    dcd     0xe5840034
    dcd     0xe5940000
    dcd     0xe59023a8
    dcd     0xe5901004
    dcd     0xe5922004
    dcd     0xe1520001
    dcd     0x128dd018
    dcd     0x18bd8038
    dcd     0xe1d0c6b0
    dcd     0xe3a01000
    dcd     0xe3a02001
    dcd     0xe1a0380c
    dcd     0xe1a03c23
    dcd     0xe3c33080
    dcd     0xe1a03803
    dcd     0xe1a03823
    dcd     0xe3ccccff
    dcd     0xe1a03c03
    dcd     0xe18c3823
    dcd     0xe1c036b0
    dcd     0xe5940000
    bl      func_ov107_020c9264
    mov r0, #0
    dcd     0xe584006c
    dcd     0xe1d512d0
    dcd     0xe59f2014
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd018
    dcd     0xe8bd8038
    dcd     0x88888889
    dcd     0x51eb851f
    dcd     func_ov261_020d0f90
}
