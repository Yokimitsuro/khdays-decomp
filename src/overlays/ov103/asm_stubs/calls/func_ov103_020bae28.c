extern char data_ov103_020bc09c[];
extern char data_ov103_020bc0ac[];
extern char data_ov103_020bc0c0[];
extern char data_ov103_020bc120[];
extern void func_ov022_020b14a4(void);
extern void func_ov022_020b15b0(void);
extern void func_ov022_020b1cec(void);

asm void func_ov103_020bae28(void)
{
    dcd     0xe92d4070
    dcd     0xe59f1090
    dcd     0xe1a05000
    dcd     0xe2850fbe
    dcd     0xe5911000
    dcd     0xe2804a02
    dcd     0xe3a00000
    dcd     0xe281202c
    dcd     0xe5c40334
    dcd     0xe5d50009
    dcd     0xe3a01003
    dcd     0xe2826b0b
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
    dcd     0xe3a02001
    dcd     0xe286300c
    bl      func_ov022_020b14a4
    dcd     0xe5840344
    dcd     0xe5d51009
    dcd     0xe59f0034
    dcd     0xe2863f93
    dcd     0xe3a02002
    bl      func_ov022_020b14a4
    dcd     0xe5840348
    dcd     0xe2850eda
    dcd     0xe3a010d5
    bl      func_ov022_020b1cec
    dcd     0xe5d40334
    dcd     0xe380000f
    dcd     0xe5c40334
    dcd     0xe8bd8070
    dcd     data_ov103_020bc120
    dcd     data_ov103_020bc09c
    dcd     data_ov103_020bc0ac
    dcd     data_ov103_020bc0c0
}
