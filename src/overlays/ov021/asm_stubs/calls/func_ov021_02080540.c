extern void func_01fffe14(void);
extern void func_02023e80(void);
extern void func_02030670(void);
extern void func_02033b24(void);
extern void func_02033d0c(void);
extern void func_ov002_0206b758(void);
extern void func_ov002_02072754(void);
extern void func_ov022_020881f8(void);
extern void func_ov022_02088474(void);

asm void func_ov021_02080540(void)
{
    dcd     0xe92d4010
    dcd     0xe5d12000
    dcd     0xe1a04000
    dcd     0xe3520000
    dcd     0x18bd8010
    dcd     0xe1d120d4
    dcd     0xe2840c02
    dcd     0xe3a01000
    dcd     0xe5c422bc
    dcd     0xe1c01bbe
    bl      func_02030670
    dcd     0xe3500000
    dcd     0x13a00001
    dcd     0x1a000004
    dcd     0xe3a00002
    bl      func_02023e80
    dcd     0xe3500000
    dcd     0x13e00000
    dcd     0x03a00001
    dcd     0xe5c402bd
    dcd     0xe3a00002
    dcd     0xe5c402b4
    bl      func_ov002_0206b758
    dcd     0xe3500000
    dcd     0x08bd8010
    bl      func_01fffe14
    dcd     0xe2841c02
    dcd     0xe1d11bdc
    dcd     0xe1510000
    dcd     0x1a000003
    mov r0, #0
    dcd     0xe3a0100f
    bl      func_02033b24
    dcd     0xe8bd8010
    bl      func_01fffe14
    bl      func_ov022_02088474
    bl      func_ov002_02072754
    dcd     0xe5d41010
    dcd     0xe1510000
    dcd     0x18bd8010
    bl      func_01fffe14
    bl      func_ov022_020881f8
    dcd     0xe1a02000
    mov r0, #0
    dcd     0xe1a03000
    dcd     0xe3a0100f
    bl      func_02033d0c
    dcd     0xe8bd8010
}
