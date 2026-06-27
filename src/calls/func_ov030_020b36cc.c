extern void func_ov022_020b14a4(void);
extern void func_ov022_020b15b0(void);
extern void func_ov022_020b1cec(void);
extern int data_ov030_020b5960;
extern int data_ov030_020b5970;
extern int data_ov030_020b5a00;

asm void func_ov030_020b36cc(void)
{
    dcd     0xe92d4070
    dcd     0xe59f1078
    dcd     0xe1a05000
    dcd     0xe2850fbe
    dcd     0xe5911000
    dcd     0xe2804a02
    dcd     0xe3a00000
    dcd     0xe2812ecb
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
    dcd     0xe2863f8d
    dcd     0xe3a02001
    bl      func_ov022_020b14a4
    dcd     0xe5840344
    dcd     0xe2850eda
    dcd     0xe3a010d0
    bl      func_ov022_020b1cec
    dcd     0xe5d40334
    dcd     0xe380000b
    dcd     0xe5c40334
    dcd     0xe8bd8070
    dcd     data_ov030_020b5a00
    dcd     data_ov030_020b5960
    dcd     data_ov030_020b5970
}
