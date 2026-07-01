extern void func_ov107_020c9264(void);
extern void func_ov219_020d05dc(void);
extern void func_ov107_020c5af8(void);
extern void VEC_Subtract(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov219_020d134c(void);

asm void func_ov219_020d1268(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd00c
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01006
    dcd     0xe5940000
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe5940000
    dcd     0xe3a01000
    bl      func_ov219_020d05dc
    dcd     0xe5940000
    dcd     0xe5943008
    dcd     0xe59f10a0
    dcd     0xe3a02006
    bl      func_ov107_020c5af8
    dcd     0xe5941000
    dcd     0xe2810c01
    dcd     0xe1d00cd6
    dcd     0xe3500003
    dcd     0x1a000019
    dcd     0xe2810c02
    dcd     0xe1d001fa
    dcd     0xe3500000
    dcd     0x1a000008
    dcd     0xe5912388
    dcd     0xe5921008
    dcd     0xe1a00c01
    dcd     0xe1a00c20
    dcd     0xe3800002
    dcd     0xe3c110ff
    dcd     0xe20000ff
    dcd     0xe1810000
    dcd     0xe5820008
    dcd     0xe5940040
    dcd     0xe3500000
    dcd     0x0a000009
    dcd     0xe5941000
    dcd     0xe28d2000
    dcd     0xe2800e19
    dcd     0xe28110b0
    bl      VEC_Subtract
    dcd     0xe59d0000
    dcd     0xe59d1008
    bl      func_020050b4
    dcd     0xe5840010
    dcd     0xe584000c
    mov r0, #0
    dcd     0xe5840040
    dcd     0xe1d512d0
    dcd     0xe59f2010
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd8030
    dcd     0x00000136
    dcd     func_ov219_020d134c
}
