extern void func_ov022_020b15b0(void);
extern void func_ov022_020b14a4(void);
extern void func_ov022_020b1cec(void);
extern void data_ov039_020b55a4(void);
extern void data_ov039_020b55b4(void);

asm void func_ov039_020b3ca8(void)
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
    dcd     0xe5952020
    dcd     0xe5d51009
    dcd     0xe2823004
    dcd     0xe59f0048
    dcd     0xe3a02000
    bl      func_ov022_020b14a4
    dcd     0xe5840340
    dcd     0xe2850a02
    dcd     0xe5900644
    dcd     0xe5d51009
    dcd     0xe590200c
    dcd     0xe59f002c
    dcd     0xe2823028
    dcd     0xe3a02001
    bl      func_ov022_020b14a4
    dcd     0xe5840344
    dcd     0xe2850eda
    dcd     0xe3a010cd
    bl      func_ov022_020b1cec
    dcd     0xe5d40334
    dcd     0xe380000b
    dcd     0xe5c40334
    dcd     0xe8bd8038
    dcd     data_ov039_020b55a4
    dcd     data_ov039_020b55b4
}
