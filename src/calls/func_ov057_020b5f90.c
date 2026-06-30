extern void func_ov022_020b15b0(void);
extern void func_ov022_020b14a4(void);
extern void func_ov022_020b1cec(void);
extern void data_ov057_020b74a0(void);
extern void data_ov057_020b7410(void);
extern void data_ov057_020b7420(void);

asm void func_ov057_020b5f90(void)
{
    dcd     0xe92d4070
    dcd     0xe1a05000
    dcd     0xe2850fbe
    dcd     0xe2804a02
    dcd     0xe3a00000
    dcd     0xe5c40334
    dcd     0xe5d50009
    dcd     0xe3a01002
    bl      func_ov022_020b15b0
    dcd     0xe59f0058
    dcd     0xe5952020
    dcd     0xe5900000
    dcd     0xe2823004
    dcd     0xe280c02c
    dcd     0xe5d51009
    dcd     0xe59f0044
    dcd     0xe3a02000
    dcd     0xe28c6b0b
    bl      func_ov022_020b14a4
    dcd     0xe5840340
    dcd     0xe5d51009
    dcd     0xe59f0030
    dcd     0xe2863f47
    dcd     0xe3a02001
    bl      func_ov022_020b14a4
    dcd     0xe5840344
    dcd     0xe2850eda
    dcd     0xe3a010c8
    bl      func_ov022_020b1cec
    dcd     0xe5d40334
    dcd     0xe380000b
    dcd     0xe5c40334
    dcd     0xe8bd8070
    dcd     data_ov057_020b74a0
    dcd     data_ov057_020b7410
    dcd     data_ov057_020b7420
}
