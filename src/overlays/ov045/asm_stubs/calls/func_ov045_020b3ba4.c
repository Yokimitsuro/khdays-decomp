extern void func_ov022_020b15b0(void);
extern void func_ov022_020b14a4(void);
extern void func_ov022_020b1cec(void);
extern char data_ov045_020b4bd0[];
extern char data_ov045_020b4be4[];

asm void func_ov045_020b3ba4(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe2850fbe
    dcd     0xe2804a02
    mov r0, #0
    dcd     0xe5c40334
    dcd     0xe5d50009
    dcd     0xe3a01002
    bl      func_ov022_020b15b0
    dcd     0xe2850a02
    dcd     0xe5900644
    dcd     0xe5d51009
    dcd     0xe590200c
    dcd     0xe59f0044
    dcd     0xe2823028
    dcd     0xe3a02000
    bl      func_ov022_020b14a4
    dcd     0xe5840344
    dcd     0xe5952020
    dcd     0xe5d51009
    dcd     0xe2823004
    dcd     0xe59f0028
    dcd     0xe3a02001
    bl      func_ov022_020b14a4
    dcd     0xe5840340
    dcd     0xe2850eda
    dcd     0xe3a010c9
    bl      func_ov022_020b1cec
    dcd     0xe5d40334
    dcd     0xe380000b
    dcd     0xe5c40334
    dcd     0xe8bd8038
    dcd     data_ov045_020b4bd0
    dcd     data_ov045_020b4be4
}
