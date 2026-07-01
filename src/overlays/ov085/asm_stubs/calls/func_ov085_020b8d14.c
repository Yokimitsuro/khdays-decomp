extern void func_02030788(void);
extern void func_ov022_020a35f4(void);
extern char data_ov085_020b9260[];

asm void func_ov085_020b8d14(void)
{
    dcd     0xe92d4070
    dcd     0xe59f208c
    dcd     0xe1a06000
    dcd     0xe5920000
    dcd     0xe1a05001
    dcd     0xe2800ec5
    dcd     0xe2804a02
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe2860064
    dcd     0xe5962464
    dcd     0xe5901404
    dcd     0xe3822801
    dcd     0xe5862464
    dcd     0xe3811000
    dcd     0xe5801404
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe286006c
    dcd     0xe596246c
    dcd     0xe5901404
    dcd     0xe3822801
    dcd     0xe586246c
    dcd     0xe3811000
    dcd     0xe5801404
    dcd     0xe5845000
    dcd     0xe3a00001
    dcd     0xe5840004
    dcd     0xe3a02000
    dcd     0xe5842120
    dcd     0xe5842008
    dcd     0xe1a00006
    dcd     0xe3a01021
    dcd     0xe5842124
    bl      func_ov022_020a35f4
    dcd     0xe8bd8070
    dcd     data_ov085_020b9260
}
