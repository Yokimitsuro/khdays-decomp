extern void func_ov022_020b15b0(void);
extern void func_ov022_020b14a4(void);
extern void func_ov022_020b1cec(void);
extern void data_ov055_020b7690(void);
extern void data_ov055_020b76a0(void);
extern void data_ov055_020b76b4(void);

asm void func_ov055_020b5fec(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe2850fbe
    dcd     0xe2804a02
    dcd     0xe3a00000
    dcd     0xe5c40334
    dcd     0xe5d50009
    dcd     0xe3a01003
    bl      func_ov022_020b15b0
    dcd     0xe5952020
    dcd     0xe5d51009
    dcd     0xe2823004
    dcd     0xe59f006c
    dcd     0xe3a02000
    bl      func_ov022_020b14a4
    dcd     0xe5840340
    dcd     0xe2850a02
    dcd     0xe5900644
    dcd     0xe5d51009
    dcd     0xe590203c
    dcd     0xe59f0050
    dcd     0xe2823028
    dcd     0xe3a02001
    bl      func_ov022_020b14a4
    dcd     0xe5840344
    dcd     0xe2853a02
    dcd     0xe5933644
    dcd     0xe5d51009
    dcd     0xe593306c
    dcd     0xe59f0030
    dcd     0xe3a02002
    dcd     0xe2833028
    bl      func_ov022_020b14a4
    dcd     0xe5840348
    dcd     0xe2850eda
    dcd     0xe3a010cc
    bl      func_ov022_020b1cec
    dcd     0xe5d40334
    dcd     0xe380000f
    dcd     0xe5c40334
    dcd     0xe8bd8038
    dcd     data_ov055_020b7690
    dcd     data_ov055_020b76a0
    dcd     data_ov055_020b76b4
}
