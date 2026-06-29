extern char data_ov096_020bc050[];
extern char data_ov096_020bc060[];
extern char data_ov096_020bc0c0[];
extern void func_ov022_020b14a4(void);
extern void func_ov022_020b15b0(void);
extern void func_ov022_020b1cec(void);

asm void func_ov096_020bad78(void)
{
    dcd     0xe92d4070
    dcd     0xe59f1078
    dcd     0xe1a05000
    dcd     0xe2850fbe
    dcd     0xe5911000
    dcd     0xe2804a02
    dcd     0xe3a00000
    dcd     0xe2812ec5
    dcd     0xe5c40334
    dcd     0xe5d50009
    dcd     0xe3a01002
    dcd     0xe2826a02
    bl      func_ov022_020b15b0
    dcd     0xe5952020
    dcd     0xe5d51009
    dcd     0xe2823004
    dcd     0xe59f0040
    dcd     0xe3a02000
    bl      func_ov022_020b14a4
    dcd     0xe5840340
    dcd     0xe5d51009
    dcd     0xe59f0030
    dcd     0xe286300c
    dcd     0xe3a02001
    bl      func_ov022_020b14a4
    dcd     0xe5840344
    dcd     0xe2850eda
    dcd     0xe3a010ce
    bl      func_ov022_020b1cec
    dcd     0xe5d40334
    dcd     0xe380000b
    dcd     0xe5c40334
    dcd     0xe8bd8070
    dcd     data_ov096_020bc0c0
    dcd     data_ov096_020bc050
    dcd     data_ov096_020bc060
}
