extern char data_ov099_020bcb2c[];
extern char data_ov099_020bcb3c[];
extern void func_ov022_020b14a4(void);
extern void func_ov022_020b15b0(void);
extern void func_ov022_020b1cec(void);

asm void func_ov099_020baf4c(void)
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
    dcd     0xe59f0040
    dcd     0xe3a02000
    bl      func_ov022_020b14a4
    dcd     0xe5840340
    dcd     0xe2852fb7
    dcd     0xe2823b0b
    dcd     0xe5d51009
    dcd     0xe59f0028
    dcd     0xe3a02001
    bl      func_ov022_020b14a4
    dcd     0xe5840344
    dcd     0xe2850eda
    dcd     0xe3a010d1
    bl      func_ov022_020b1cec
    dcd     0xe5d40334
    dcd     0xe380000b
    dcd     0xe5c40334
    dcd     0xe8bd8038
    dcd     data_ov099_020bcb2c
    dcd     data_ov099_020bcb3c
}
