extern void FX_Sqrt(void);
extern void func_01fffd70(void);
extern void func_01fffd8c(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov107_020c5c54(void);
extern void func_ov107_020cab14(void);

asm void func_ov289_020d7038(void)
{
    dcd     0xe92d40f8
    dcd     0xe1a05000
    dcd     0xe8950011
    dcd     0xe5941034
    dcd     0xe590002c
    dcd     0xe0810000
    dcd     0xe5840034
    dcd     0xe3500a01
    dcd     0xb8bd80f8
    dcd     0xe3a00a01
    dcd     0xe5840034
    dcd     0xe5940000
    dcd     0xe2801e19
    bl      func_ov107_020c5c54
    dcd     0xe5940000
    dcd     0xe59003b8
    dcd     0xe3500000
    dcd     0xda000012
    bl      func_02023eb4
    dcd     0xe5941000
    dcd     0xe1a06000
    dcd     0xe2810fe6
    bl      func_01fffd70
    dcd     0xe1b01000
    dcd     0xe3a07000
    dcd     0x0a00000a
    dcd     0xe1570006
    dcd     0xba000002
    dcd     0xe5940000
    bl      func_ov107_020c5c54
    dcd     0xea000005
    dcd     0xe5940000
    dcd     0xe2800fe6
    bl      func_01fffd8c
    dcd     0xe1b01000
    dcd     0xe2877001
    dcd     0x1afffff4
    dcd     0xe5940000
    dcd     0xe28d1000
    bl      func_ov107_020cab14
    dcd     0xe3500000
    dcd     0x0a000003
    dcd     0xe59d0000
    bl      FX_Sqrt
    dcd     0xe3500b02
    dcd     0xd8bd80f8
    dcd     0xe594e000
    dcd     0xe3a03001
    dcd     0xe1dec6b0
    dcd     0xe1a00005
    dcd     0xe3a02000
    dcd     0xe1a0180c
    dcd     0xe1a01c21
    dcd     0xe3811001
    dcd     0xe3ccccff
    dcd     0xe1a01c01
    dcd     0xe18c1821
    dcd     0xe1ce16b0
    dcd     0xe5941000
    dcd     0xe5c131c7
    dcd     0xe1d512d0
    bl      func_0203c634
    dcd     0xe8bd80f8
}
