extern char data_ov090_020bcb9c[];
extern char data_ov090_020bcbac[];
extern char data_ov090_020bcbc0[];
extern void func_ov022_020b14a4(void);
extern void func_ov022_020b15b0(void);
extern void func_ov022_020b1cec(void);

asm void func_ov090_020bb434(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe2850fbe
    dcd     0xe2804a02
    mov r0, #0
    dcd     0xe5c40334
    dcd     0xe5d50009
    dcd     0xe3a01003
    bl      func_ov022_020b15b0
    dcd     0xe5952020
    dcd     0xe5d51009
    dcd     0xe2823004
    dcd     0xe59f0058
    dcd     0xe3a02000
    bl      func_ov022_020b14a4
    dcd     0xe5840340
    dcd     0xe5d51009
    dcd     0xe59f0048
    dcd     0xe2853ef1
    dcd     0xe3a02001
    bl      func_ov022_020b14a4
    dcd     0xe5840344
    dcd     0xe2853f6b
    dcd     0xe5d51009
    dcd     0xe59f0030
    dcd     0xe3a02002
    dcd     0xe2833b03
    bl      func_ov022_020b14a4
    dcd     0xe5840348
    dcd     0xe2850eda
    dcd     0xe3a010c6
    bl      func_ov022_020b1cec
    dcd     0xe5d40334
    dcd     0xe380000f
    dcd     0xe5c40334
    dcd     0xe8bd8038
    dcd     data_ov090_020bcb9c
    dcd     data_ov090_020bcbac
    dcd     data_ov090_020bcbc0
}
