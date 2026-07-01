extern void func_020235d0(void);
extern void func_ov002_020573cc(void);
extern void func_ov002_0206b828(void);
extern void func_ov002_0206b7a4(void);
extern void func_01fffde0(void);
extern void func_ov002_0206d144(void);
extern void func_ov002_0206d194(void);
extern void func_ov022_02088c10(void);
extern void func_ov017_020804d4(void);

asm void func_ov017_020805d0(void)
{
    dcd     0xe92d40f8
    dcd     0xe1a05000
    dcd     0xe1a04001
    dcd     0xe1d501b4
    dcd     0xe5d51016
    bl      func_020235d0
    dcd     0xe59f10dc
    dcd     0xe0000001
    dcd     0xe1a00780
    dcd     0xe1a06820
    bl      func_ov002_020573cc
    dcd     0xe3500000
    dcd     0x1a000005
    bl      func_ov002_0206b828
    dcd     0xe3500000
    dcd     0x1a000002
    bl      func_ov002_0206b7a4
    dcd     0xe3500000
    dcd     0x0a000001
    mov r0, #0
    dcd     0xe8bd80f8
    dcd     0xe3160001
    dcd     0x05d501b4
    dcd     0x03500003
    dcd     0x1a000023
    dcd     0xe5d40000
    bl      func_01fffde0
    dcd     0xe2851c01
    dcd     0xe1a06000
    dcd     0xe1d10bf6
    bl      func_ov002_0206d144
    dcd     0xe1a00800
    dcd     0xe1a00840
    bl      func_ov002_0206d194
    dcd     0xe1a07000
    dcd     0xe59604ec
    dcd     0xe1d724f2
    dcd     0xe590c1c0
    dcd     0xe1d734b0
    dcd     0xe35c0000
    dcd     0xe5d511b9
    dcd     0xe20220ff
    dcd     0x03a00001
    dcd     0x0a000000
    dcd     0xe12fff3c
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe2852c01
    dcd     0xe5d40000
    dcd     0xe1d714f0
    dcd     0xe1d22bd9
    bl      func_ov022_02088c10
    mov r0, #0
    dcd     0xe8bd80f8
    dcd     0xe1a00005
    bl      func_ov017_020804d4
    dcd     0xe1d501b2
    dcd     0xe3c00008
    dcd     0xe1c501b2
    dcd     0xe5d40000
    dcd     0xe5c501b8
    mov r0, #0
    dcd     0xe8bd80f8
    dcd     0x0000fffe
}
