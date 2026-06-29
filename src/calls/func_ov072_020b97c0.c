extern char data_ov072_020ba724[];
extern char data_ov072_020ba734[];
extern char data_ov072_020ba748[];
extern char data_ov072_020ba7a0[];
extern void func_ov022_020b14a4(void);
extern void func_ov022_020b15b0(void);
extern void func_ov022_020b1cec(void);

asm void func_ov072_020b97c0(void)
{
    dcd     0xe92d40f8
    dcd     0xe59f1098
    dcd     0xe1a06000
    dcd     0xe2860fbe
    dcd     0xe5914000
    dcd     0xe2805a02
    dcd     0xe3a00000
    dcd     0xe5c50334
    dcd     0xe5d60009
    dcd     0xe3a01003
    bl      func_ov022_020b15b0
    dcd     0xe2860a02
    dcd     0xe5900644
    dcd     0xe5962020
    dcd     0xe5d61009
    dcd     0xe590703c
    dcd     0xe59f0060
    dcd     0xe2823004
    dcd     0xe3a02000
    bl      func_ov022_020b14a4
    dcd     0xe5850340
    dcd     0xe5d61009
    dcd     0xe2873028
    dcd     0xe59f0048
    dcd     0xe3a02001
    bl      func_ov022_020b14a4
    dcd     0xe2841fa1
    dcd     0xe2813b0b
    dcd     0xe5850344
    dcd     0xe59f0034
    dcd     0xe5d61009
    dcd     0xe3a02002
    bl      func_ov022_020b14a4
    dcd     0xe5850348
    dcd     0xe2860eda
    dcd     0xe3a010c5
    bl      func_ov022_020b1cec
    dcd     0xe5d50334
    dcd     0xe380000f
    dcd     0xe5c50334
    dcd     0xe8bd80f8
    dcd     data_ov072_020ba7a0
    dcd     data_ov072_020ba724
    dcd     data_ov072_020ba734
    dcd     data_ov072_020ba748
}
