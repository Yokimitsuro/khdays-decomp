extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov130_020cc468(void);
extern void func_ov130_020cd248(void);

asm void func_ov130_020cd1bc(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe8950011
    dcd     0xe594102c
    dcd     0xe590002c
    dcd     0xe0810000
    dcd     0xe584002c
    dcd     0xe3500f66
    dcd     0xba00000b
    dcd     0xe5d40041
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe3a01b03
    dcd     0xe3a00b01
    dcd     0xe5841030
    dcd     0xe5840034
    dcd     0xe584001c
    mov r0, #1
    dcd     0xe5c40041
    dcd     0xe1a00005
    bl      func_ov130_020cc468
    dcd     0xe5940004
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x18bd8038
    dcd     0xe5940000
    dcd     0xe3a01005
    dcd     0xe3a02001
    bl      func_ov107_020c9264
    dcd     0xe1d512d0
    dcd     0xe59f2008
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov130_020cd248
}
